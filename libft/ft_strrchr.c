/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drina <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 21:00:32 by drina             #+#    #+#             */
/*   Updated: 2020/05/01 21:09:42 by drina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				count;
	unsigned char	symbol;

	count = ft_strlen(s);
	symbol = (unsigned char)c;
	while (count >= 0)
	{
		if (s[count] == symbol)
			return ((char *)&s[count]);
		count--;
	}
	return (0);
}
