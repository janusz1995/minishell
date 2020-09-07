/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drina <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 20:14:51 by drina             #+#    #+#             */
/*   Updated: 2020/05/05 16:41:42 by drina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	check_symbol(char a, const char *line)
{
	size_t	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == a)
			return (1);
		i++;
	}
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	size_t	count;
	size_t	len_s1;
	size_t	i;
	char	*list;

	count = 0;
	i = 0;
	if (!s1 || !set)
		return (NULL);
	len_s1 = ft_strlen(s1);
	while (len_s1 > 0 && check_symbol(s1[len_s1 - 1], set) == 1)
		len_s1--;
	if (len_s1 > 0)
	{
		while (check_symbol(s1[count], set) == 1 && s1[count] != '\0')
			count++;
	}
	if (!(list = (char *)malloc(((len_s1 - count) + 1) * sizeof(char))))
		return (NULL);
	while (count < len_s1)
		list[i++] = s1[count++];
	list[i] = '\0';
	return (list);
}
