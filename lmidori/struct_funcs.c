/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 21:46:25 by lmidori           #+#    #+#             */
/*   Updated: 2020/10/01 16:09:35 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int			init_struct(t_arg *arg, int len)
{
	if (len == -1)
		return (-1);
	arg->len = len;
	if ((arg->arg = (char *)ft_calloc(sizeof(char), (len + 1))) == NULL)
		return (-1);
	arg->arg[len] = '\0';
	arg->j = 0;
	return (1);
}

int			fool_strcut(t_all *all, t_list_args **list)
{
	t_list_args *tmp;

	tmp = *list;
	ft_init_struct(all);
	if (tmp)
	{
		if (tmp->spec_flag == 2)
			all->equal = 1;
		while (tmp && tmp->spec_flag != 1)
		{
			ft_lstadd_back_arg(&(all->args), ft_lstnew_arg(tmp->content, tmp->spec_flag));
			if (!all->args)		// ???
				return (-1);
			tmp = tmp->next;
		}

		if (tmp && tmp->spec_flag)
		{
			all->spec = tmp->content;
			tmp = tmp->next;
		}
	}
	*list = tmp;
	return (1);
}

void		ft_init_struct(t_all *all)
{
	all->args = NULL;
	all->spec = NULL;
	all->equal = 0;
}

void		ft_clear_strcut(t_all *all)
{
	if (all->spec != NULL)
		free(all->spec);
	all->spec = NULL;
	ft_lstclear_args(&(all->args), free);
	// free(all);
}
