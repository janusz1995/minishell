/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 19:53:24 by lmidori           #+#    #+#             */
/*   Updated: 2020/10/05 16:50:47 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void		cmd_env(t_env *head)
{
	t_env *tmp;

	tmp = head;
	while (tmp != NULL)
	{
		if (tmp->visible == 1)
		{
			ft_putstr_fd(tmp->key_value[0], 1);
			write(1, "=", 1);
			ft_putstr_fd(tmp->key_value[1], 1);
			write(1, "\n", 1);
		}
		tmp = tmp->next;
	}
	error = 0;
}
