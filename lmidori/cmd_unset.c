/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 20:58:05 by lmidori           #+#    #+#             */
/*   Updated: 2020/10/03 15:58:20 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void		error_unset(char *name)
{
	ft_putstr_fd("minishell: unset: `", 1);
	ft_putstr_fd(name, 1);
	ft_putstr_fd("': not a valid identifier\n", 1);
	error = 1;
}

void			cmd_unset(t_env **head, char *del_str)
{
	t_env		*tmp;
	t_env		*next_elem;

	tmp = *head;
	next_elem = *head;
	error = 0;
	if (!check_name(del_str, '='))
	{
		error_unset(del_str);
		return ;
	}
	while (next_elem && ft_strncmp(next_elem->key_value[0],
		del_str, ft_strlen(next_elem->key_value[0]) + 1) != 0)
		next_elem = next_elem->next;
	if (next_elem == NULL)
	{
		return ;
	}
	while (tmp && ft_strncmp(tmp->next->key_value[0],
		del_str, ft_strlen(tmp->next->key_value[0]) + 1) != 0)
		tmp = tmp->next;
	tmp->next = next_elem->next;
	free(next_elem->key_value[0]);
	free(next_elem->key_value[1]);
	free(next_elem);
	next_elem = NULL;
}
