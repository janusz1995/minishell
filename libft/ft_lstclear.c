/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drina <drina@marvin.42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 21:46:45 by drina             #+#    #+#             */
/*   Updated: 2020/05/07 15:38:00 by drina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*list;

	if (!lst)
		return ;
	while (*lst)
	{
		list = *lst;
		if (del)
			del(list->content);
		(*lst) = (*lst)->next;
		free(list);
	}
}
