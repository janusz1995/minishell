/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 22:03:26 by drina             #+#    #+#             */
/*   Updated: 2020/10/02 19:25:47 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*list;
	unsigned int	count;

	count = 0;
	if (!s || !f)
		return (NULL);
	list = (char *)xmalloc((ft_strlen(s) + 1) * sizeof(char));
	if (!list)
		return (NULL);
	while (s[count] != '\0')
	{
		list[count] = f(count, s[count]);
		count++;
	}
	list[count] = '\0';
	return (list);
}
