/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 18:31:40 by lmidori           #+#    #+#             */
/*   Updated: 2020/10/05 23:21:00 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int			export_if_in_list(t_env **envp, char *name, t_list_args *tmp)
{
	char	*value;

	if (ft_strchr(tmp->content, '=') != NULL)
	{
		if (!(value = get_value_env(&(tmp->content[ft_strlen(name) + 1]))))
		{
			free(name);
			return (0);
		}
		redact_env(envp, name, value);
		free(value);
	}
	else
		redact_env(envp, name, NULL);
	return (1);
}

int			export_if_not_in_list(t_env **envp, char *name, t_list_args *tmp)
{
	char	*value;

	if (ft_strchr(tmp->content, '=') != NULL)
	{
		if (!(value = get_value_env(&(tmp->content[ft_strlen(name) + 1]))))
		{
			free(name);
			return (0);
		}
		add_back(envp, lst_new_env(name, value, 1));
		free(value);
	}
	else
		add_back(envp, lst_new_env(name, NULL, 1));
	return (1);
}

void		error_export(char *name)
{
	ft_putstr_fd("minishell: export: `", 1);
	ft_putstr_fd(name, 1);
	ft_putstr_fd("': not a valid identifier\n", 1);
	error = 1;
}

void		cmd_export(t_env **envp, t_list_args *args)
{
	t_list_args		*tmp;
	char			*name;

	tmp = args->next;
	error = 0;
	if (!args->next)
		print_export(envp);
	else
		while (tmp)
		{
			if (!(name = get_name_env(tmp->content, '=')))
			{
				error_export(tmp->content);
				tmp = tmp->next;
				continue;
			}
			else if (find_in_env(envp, name))
			{
				if (!export_if_in_list(envp, name, tmp))
					return ;
			}
			else if (!export_if_not_in_list(envp, name, tmp))
				return ;
			free(name);
			tmp = tmp->next;
		}
}
