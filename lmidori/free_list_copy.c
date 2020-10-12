/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list_copy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 18:16:51 by lmidori           #+#    #+#             */
/*   Updated: 2020/10/10 18:17:09 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void				free_list_copy(t_head_struct *head_struct)
{
	t_list_args		*tmp;

	head_struct->copy_all->equal = 0;
	free(head_struct->copy_all->spec);
	while (head_struct->copy_all->args)
	{
		tmp = head_struct->copy_all->args;
		head_struct->copy_all->args = head_struct->copy_all->args->next;
		free(tmp);
		tmp = NULL;
	}
	head_struct->copy_all->args = NULL;
	head_struct->copy_all->spec = NULL;
	free(head_struct->copy_all);
	head_struct->copy_all = NULL;
}
