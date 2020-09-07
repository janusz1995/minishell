/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drina <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 19:00:47 by drina             #+#    #+#             */
/*   Updated: 2020/05/03 17:34:56 by drina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t count;

	count = 0;
	if (size > 0)
	{
		while (count < size - 1 && src[count] != '\0')
		{
			dst[count] = src[count];
			count++;
		}
		dst[count] = '\0';
	}
	return (ft_strlen(src));
}
