/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drina <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 21:10:58 by drina             #+#    #+#             */
/*   Updated: 2020/05/07 16:34:11 by drina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t count;
	size_t tmp;
	size_t i;

	count = 0;
	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	while (count < len && haystack[count] != '\0')
	{
		i = 0;
		tmp = count;
		while (needle[i++] == haystack[tmp++] && tmp <= len)
		{
			if (needle[i] == '\0')
				return ((char *)&haystack[count]);
		}
		count++;
	}
	return (NULL);
}
