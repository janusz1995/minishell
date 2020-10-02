/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 21:48:59 by lmidori           #+#    #+#             */
/*   Updated: 2020/10/02 19:33:03 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char		*get_home_dir(t_env *env)
{
	char	*str;

	str = NULL;
	while (env->next != NULL)
	{
		if ((ft_strncmp(env->key_value[0], "HOME", 5)) == 0)
		{
			str = ft_strdup(env->key_value[1]);
		}
		env = env->next;
	}
	if (!str)
		str = ft_strdup("");
	return (str);
}

char		*get_arg_env(char *tmp, t_env *env)
{
	char	*out;
	char	*value;

	out = NULL;
	value = "";
	if (*tmp != '\0')
		while (env)
		{
			if ((ft_strncmp(env->key_value[0], tmp,
				ft_strlen(env->key_value[0]) + 1)) == 0)
			{
				value = env->key_value[1];
				break ;
			}
			env = env->next;
		}
	if (value)
		out = ft_strdup(value);
	else
		out = ft_strdup("");
	return (out);
}
