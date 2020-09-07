/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drina <drina@marvin.42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 22:03:26 by drina             #+#    #+#             */
/*   Updated: 2020/05/06 17:45:14 by drina            ###   ########.fr       */
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
	list = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
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
