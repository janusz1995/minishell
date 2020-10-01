/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 21:18:16 by lmidori           #+#    #+#             */
/*   Updated: 2020/10/01 21:18:33 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

int			init_env(char *var, t_env **env)
{
	char	*name;
	char	*value;
	t_env	*tmp;

	tmp = *env;
	if (!(name = get_name_env(var, '=')))
		return (0);
	if (!(value = get_value_env(&var[ft_strlen(name) + 1])))
		return (0);
	while (tmp && ft_strncmp(name, tmp->key_value[0], ft_strlen(name) + 1) != 0)
		tmp = tmp->next;
	if (!tmp)
		add_back(env, lst_new_env(name, value, 0));
	else
	{
		free(tmp->key_value[1]);
		tmp->key_value[1] = ft_strdup(value);
	}
	free(value);
	free(name);
	return (1);
}
