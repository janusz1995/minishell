/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drina <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 14:43:00 by drina             #+#    #+#             */
/*   Updated: 2020/05/02 16:38:24 by drina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			count;
	unsigned char	*line_s1;
	unsigned char	*line_s2;

	line_s1 = (unsigned char *)s1;
	line_s2 = (unsigned char *)s2;
	count = 0;
	while (count < n && (line_s1[count] || line_s2[count]))
	{
		if (line_s1[count] == line_s2[count])
			count++;
		else
			return (line_s1[count] - line_s2[count]);
	}
	return (0);
}
