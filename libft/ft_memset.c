/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drina <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 21:45:49 by drina             #+#    #+#             */
/*   Updated: 2020/05/01 15:05:40 by drina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			count;
	unsigned char	a;
	unsigned char	*h;

	h = (unsigned char *)b;
	a = (unsigned char)c;
	count = 0;
	while (count < len)
	{
		h[count] = a;
		count++;
	}
	return (b);
}
