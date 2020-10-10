/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 21:17:59 by lmidori           #+#    #+#             */
/*   Updated: 2020/10/10 21:55:40 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char		*get_value_env(char *var)
{
	char	*out;
	int		i;
	int		len;

	len = ft_strlen(var);
	if (!(out = (char *)xmalloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = -1;
	out[len] = '\0';
	while (var[++i] != '\0')
		out[i] = var[i];
	return (out);
}
