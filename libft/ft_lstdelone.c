/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drina <drina@marvin.42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 21:28:47 by drina             #+#    #+#             */
/*   Updated: 2020/05/07 15:40:08 by drina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	t_list	*list;

	if (!lst)
		return ;
	if (del)
		del(lst->content);
	list = lst;
	lst = lst->next;
	free(list);
}
