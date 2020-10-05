/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_new_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 18:41:02 by lmidori           #+#    #+#             */
/*   Updated: 2020/10/05 16:48:51 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int			check_name(char *var, char ch)
{
	int		i;

	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (0);
	i = -1;
	while (var[++i] != ch && var[i] != '\0')
	{
		if (!ft_isdigit(var[i]) && !ft_isalpha(var[i]) && var[i] != '_')
			return (0);
	}
	return (i);
}

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

int			find_env(t_head_struct *head_struct)
{
	t_list_args	*arg;

	arg = head_struct->all.args;
	while (arg != NULL)
	{
		if (!(init_env(arg->content, &(head_struct->env))))
			return (-1);
		arg = arg->next;
	}
	return (1);
}

int			add_new_env(t_head_struct *head_struct, char **str)
{
	t_list_args *arg;
	int			flag;
	int			i;

	i = 0;
	flag = 1;
	arg = head_struct->all.args;
	while (arg && arg->spec_flag == 2)
	{
		if (!(flag = check_name(arg->content, '=')))
			break ;
		arg = arg->next;
		i++;
	}
	if (!arg && (head_struct->all.spec == NULL
		|| *head_struct->all.spec != '|'))
		find_env(head_struct);
	else if (!flag || (arg && arg->spec_flag != 2))
	{
		head_struct->all.equal = 0;
		select_cmd(head_struct, &str[i], arg);
	}
	return (1);
}
