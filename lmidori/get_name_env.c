/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_name_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 20:56:51 by lmidori           #+#    #+#             */
/*   Updated: 2020/10/02 22:44:02 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char		*get_name_env(char *var, char ch)
{
	char	*name;
	int		i;

	if (!(i = check_name(var, ch)))
		return (NULL);
	name = (char *)xmalloc(sizeof(char) * (i + 1));
	name[i] = '\0';
	i = 0;
	while (var[i] != ch && var[i] != '\0')
	{
		name[i] = var[i];
		i++;
	}
	return (name);
}
