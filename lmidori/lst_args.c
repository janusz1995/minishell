/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 21:10:38 by lmidori           #+#    #+#             */
/*   Updated: 2020/09/12 22:46:06 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list_args	*ft_lstnew_arg(void *content, int flag)
{
	t_list_args	*list;

	list = (t_list_args *)malloc(sizeof(t_list_args));
	if (!list)
		return (NULL);
	list->content = content;
	list->spec_flag = flag;
	list->next = NULL;
	return (list);
}

t_list_args	*ft_lstlast_arg(t_list_args *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_arg(t_list_args **lst, t_list_args *new)
{
	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
		ft_lstlast_arg(*lst)->next = new;
}

void	ft_lstclear_args(t_list_args **lst, void (*del)(void*))
{
	t_list_args	*list;

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

void	ft_lst_print(t_list_args *list)
{
	ft_putstr_fd("		START LIST\n", 2);
	while (list)
	{
		ft_putstr_fd((char *)list->content, 1);
		ft_putnbr_fd(list->spec_flag, 1);
		write(1, "\n", 1);
		list = list->next;
	}
	ft_putstr_fd("		END LIST\n", 2);
}
