/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 21:59:29 by drina             #+#    #+#             */
/*   Updated: 2020/10/01 16:39:42 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static	void	clear(char **last_list)
{
	if (*last_list)
	{
		free(*last_list);
		*last_list = NULL;
	}
}

static char		*last(char **last_list, char **line)
{
	char	*tmp;
	char	*tmp_free;

	tmp = NULL;
	if (*last_list)
	{
		if ((tmp = ft_strchr_gnl(*last_list, '\n')))
		{
			*tmp = '\0';
			*line = ft_strdup_gnl(*last_list);
			tmp_free = *last_list;
			*last_list = ft_strdup_gnl(++tmp);
			free(tmp_free);
		}
		else
		{
			*line = ft_strdup_gnl(*last_list);
			clear(&(*last_list));
		}
	}
	else
		*line = ft_strdup_gnl("");
	return (tmp);
}

static int		returns(ssize_t count, char *pointer, char **last_list)
{
	if (count > 0 || pointer)
		return (1);
	clear(&(*last_list));
	return (count);
}

void			free_and_line(char **line, char *list)
{
	char	*tmp;

	tmp = *line;
	*line = ft_strjoin_gnl(*line, list);
	free(tmp);
}

int				get_next_line(int fd, char **line)
{
	ssize_t		count;
	char		*tmp;
	char		*pointer;
	char		list[BUFFER_SIZE + 1];
	static char	*last_list;

	count = -1;
	if (fd < 0 || BUFFER_SIZE < 1 || !line || 0 > (read(fd, list, 0)))
		return (-1);
	pointer = last(&last_list, line);
	while (!pointer && 0 <= (count = read(fd, list, BUFFER_SIZE)) && list[0])
	{
		if (count == 0 && list[0])
			continue ;
		list[count] = '\0';
		if ((pointer = ft_strchr_gnl(list, '\n')))
		{
			*pointer = '\0';
			tmp = last_list;
			last_list = ft_strdup_gnl(++pointer);
			free(tmp);
		}
		free_and_line(line, list);
	}
	return (returns(count, pointer, &last_list));
}
