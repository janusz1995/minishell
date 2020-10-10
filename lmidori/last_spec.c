/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_spec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 18:17:26 by lmidori           #+#    #+#             */
/*   Updated: 2020/10/10 18:18:04 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	last_spec_free(t_head_struct *head_struct)
{
	if (head_struct->last_spec)
	{
		free(head_struct->last_spec);
		head_struct->last_spec = NULL;
	}
}

int		check_last_spec(t_head_struct *head_struct, char *str)
{
	if (head_struct->last_spec &&
		ft_strncmp(head_struct->last_spec, ">>", 3) == 0)
	{
		if ((head_struct->fd_redir = open(str,
			O_CREAT | O_APPEND | O_WRONLY, 0644)) < 0)
		{
			last_spec_free(head_struct);
			error_and_free(head_struct, str);
			return (0);
		}
	}
	last_spec_free(head_struct);
	return (1);
}
