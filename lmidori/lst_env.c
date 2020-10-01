/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 16:01:22 by lmidori           #+#    #+#             */
/*   Updated: 2020/10/01 21:19:28 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		ft_lstlast_env(t_env *lst)
{
	int	len;

	len = 0;
	if (!lst)
		return (0);
	while (lst->next != NULL)
	{
		if (lst->visible == 1)
			len++;
		lst = lst->next;
	}
	return (len);
}
