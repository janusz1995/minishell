/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drina <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 12:52:53 by drina             #+#    #+#             */
/*   Updated: 2020/05/01 15:08:54 by drina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			count;
	unsigned char	*stroke_src;
	unsigned char	*stroke_dst;
	unsigned char	symbol;

	count = 0;
	stroke_src = (unsigned char*)src;
	stroke_dst = (unsigned char*)dst;
	symbol = (unsigned char)c;
	while (count < n)
	{
		stroke_dst[count] = stroke_src[count];
		if (stroke_dst[count] == symbol)
			return (&stroke_dst[++count]);
		count++;
	}
	return (0);
}
