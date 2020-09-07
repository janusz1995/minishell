/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drina <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 18:16:12 by drina             #+#    #+#             */
/*   Updated: 2020/05/24 17:23:06 by drina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_strlen_gnl(char *list)
{
	int i;

	i = 0;
	while (list[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup_gnl(char *last_list)
{
	int		i;
	char	*array;

	i = 0;
	while (last_list[i] != '\0')
		i++;
	if (!(array = (char *)malloc((i + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	while (last_list[i] != '\0')
	{
		array[i] = last_list[i];
		i++;
	}
	array[i] = '\0';
	return (array);
}

char	*ft_strjoin_gnl(char *line, char *list)
{
	int		count;
	int		i;
	char	*array;

	count = 0;
	i = 0;
	array = (char *)malloc(((ft_strlen_gnl(line) +
					ft_strlen_gnl(list)) + 1) * sizeof(char));
	if (!array)
		return (NULL);
	while (line[count] != '\0')
	{
		array[count] = line[count];
		count++;
	}
	while (list[i] != '\0')
		array[count++] = list[i++];
	array[count] = '\0';
	return (array);
}

char	*ft_strchr_gnl(char *line, int c)
{
	int		count;

	count = 0;
	while (line[count])
	{
		if (line[count] == (unsigned char)c)
			return ((char *)&line[count]);
		count++;
	}
	return (0);
}
