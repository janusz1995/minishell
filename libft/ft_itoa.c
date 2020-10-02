/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 21:24:13 by drina             #+#    #+#             */
/*   Updated: 2020/10/02 19:22:44 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		num(int c)
{
	int		count;

	count = 0;
	if (c == 0)
		return (1);
	if (c < 0)
		count++;
	while (c != 0)
	{
		c = c / 10;
		count++;
	}
	return (count);
}

char			*ft_itoa(int c)
{
	int			count;
	char		*list;
	long long	number;

	number = (long long)c;
	count = num(number);
	list = (char *)xmalloc((count + 1) * sizeof(char));
	if (number < 0)
	{
		list[0] = '-';
		number = -number;
	}
	list[count--] = '\0';
	while (number > 9)
	{
		list[count] = (char)((number % 10) + '0');
		number = number / 10;
		count--;
	}
	list[count] = (char)number + '0';
	return (list);
}
