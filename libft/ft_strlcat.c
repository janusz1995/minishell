/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drina <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 13:08:59 by drina             #+#    #+#             */
/*   Updated: 2020/05/03 17:34:45 by drina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	count;
	size_t	len_dst;
	size_t	len_dst_start;

	len_dst = ft_strlen(dst);
	len_dst_start = len_dst;
	count = 0;
	if (size < len_dst)
		return (ft_strlen(src) + size);
	if (size > 0)
	{
		while (len_dst < size - 1 && src[count] != '\0')
		{
			dst[len_dst] = src[count];
			len_dst++;
			count++;
		}
		dst[len_dst] = '\0';
	}
	return (len_dst_start + ft_strlen(src));
}
