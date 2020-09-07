/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drina <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 21:25:15 by drina             #+#    #+#             */
/*   Updated: 2020/05/01 15:06:25 by drina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			count;
	unsigned char	*stroke;

	stroke = (unsigned char *)s;
	count = 0;
	while (n > count)
	{
		stroke[count] = '\0';
		count++;
	}
}
