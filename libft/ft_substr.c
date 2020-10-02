/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 18:14:09 by drina             #+#    #+#             */
/*   Updated: 2020/10/02 19:26:09 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	count;
	char	*list;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		start = ft_strlen(s);
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	list = (void *)xmalloc((len + 1) * sizeof(char));
	count = 0;
	if (!list)
		return (NULL);
	while (count < len && s[start])
	{
		list[count] = s[start];
		count++;
		start++;
	}
	list[count] = '\0';
	return (list);
}
