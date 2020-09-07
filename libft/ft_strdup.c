/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drina <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 12:34:40 by drina             #+#    #+#             */
/*   Updated: 2020/05/03 17:52:59 by drina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*list;

	list = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!list)
		return (NULL);
	ft_memcpy(list, s1, ft_strlen(s1) + 1);
	return (list);
}
