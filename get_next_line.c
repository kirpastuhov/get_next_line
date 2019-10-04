/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpastukh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 19:28:57 by kpastukh          #+#    #+#             */
/*   Updated: 2019/10/04 12:33:18 by kpastukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*ft_checkline(char **stack, int fd)
{
	char	*new_str;
	char	*tmp;
	int		end;

	end = 0;
	tmp = NULL;
	while (stack[fd][end] != '\n' && stack[fd][end] != '\0')
		end++;
	if (stack[fd])
		new_str = ft_strsub(stack[fd], 0, end);
	else
		new_str = ft_strnew(0);
	if (stack[fd][end] == '\n')
		tmp = ft_strdup(&stack[fd][end + 1]);
	else
		tmp = ft_strdup(&stack[fd][end]);
	free(stack[fd]);
	stack[fd] = tmp;
	if (stack[fd] == NULL)
		ft_strdel(&stack[fd]);
	return (new_str);
}

void	ft_updstack(char **stack, char *buff, int fd)
{
	char *tmp;

	tmp = ft_strjoin(stack[fd], buff);
	free(stack[fd]);
	stack[fd] = tmp;
}

int		get_next_line(const int fd, char **line)
{
	static char		*stack[MAX_FD];
	int				bytes_read;
	char			buff[BUFF_SIZE + 1];

	if (fd < 0 || !line || read(fd, buff, 0) < 0)
		return (-1);
	while ((bytes_read = read(fd, buff, BUFF_SIZE)))
	{
		buff[bytes_read] = '\0';
		if (stack[fd] == NULL)
			stack[fd] = ft_strdup(buff);
		else
			ft_updstack(stack, buff, fd);
		ft_bzero(buff, BUFF_SIZE);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	if (ft_strlen(stack[fd]) > 0)
	{
		*line = ft_checkline(stack, fd);
		return (1);
	}
	return (0);
}
