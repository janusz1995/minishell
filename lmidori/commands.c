/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 20:20:19 by lmidori           #+#    #+#             */
/*   Updated: 2020/10/10 20:20:21 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	commands(t_head_struct *head_struct, char **str, t_list_args *args)
{
	if (check_cond(str[0]) == 1)
		no_system_cmd(head_struct, str, args);
	else
		system_cmd(head_struct, str);
}
