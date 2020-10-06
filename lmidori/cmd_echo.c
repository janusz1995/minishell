/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 17:46:57 by lmidori           #+#    #+#             */
/*   Updated: 2020/10/06 19:00:57 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void				cmd_echo(t_list_args *list)
{
	t_list_args		*tmp;
	int				flag;

	flag = 0;
	g_error = 0;
	tmp = list->next;
	if (tmp && ft_strncmp(tmp->content, "-n", ft_strlen(tmp->content) + 1) == 0)
	{
		flag = 1;
		tmp = tmp->next;
	}
	while (tmp)
	{
		write(1, tmp->content, ft_strlen(tmp->content));
		if (tmp->next)
			write(1, " ", 1);
		tmp = tmp->next;
	}
	if (!flag)
		write(1, "\n", 1);
}
