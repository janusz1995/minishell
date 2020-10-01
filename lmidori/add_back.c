/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_back.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 17:45:33 by lmidori           #+#    #+#             */
/*   Updated: 2020/10/01 17:45:53 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_back(t_env **head, t_env *new)
{
	t_env	*save_head;

	save_head = (*head);
	if (save_head == NULL)
		(*head) = new;
	else
	{
		while (save_head->next != NULL)
			save_head = save_head->next;
		save_head->next = new;
	}
}
