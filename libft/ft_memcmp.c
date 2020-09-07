/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drina <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 16:42:52 by drina             #+#    #+#             */
/*   Updated: 2020/05/01 18:51:17 by drina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			count;
	unsigned char	*line_s1;
	unsigned char	*line_s2;

	line_s1 = (unsigned char *)s1;
	line_s2 = (unsigned char *)s2;
	count = 0;
	while (count < n)
	{
		if (line_s1[count] == line_s2[count])
			count++;
		else
			return (line_s1[count] - line_s2[count]);
	}
	return (0);
}
