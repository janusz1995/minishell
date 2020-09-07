/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drina <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 19:39:08 by drina             #+#    #+#             */
/*   Updated: 2020/05/04 20:30:55 by drina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	count;
	char	*list;

	if (!s1 || !s2)
		return (NULL);
	list = (char *)malloc((ft_strlen(s1) + ft_strlen(s2)) * sizeof(char) + 1);
	count = 0;
	i = 0;
	if (!list)
		return (NULL);
	while (s1[count] != '\0')
	{
		list[count] = s1[count];
		count++;
	}
	while (s2[i] != '\0')
		list[count++] = s2[i++];
	list[count] = '\0';
	return (list);
}
