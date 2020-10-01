/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 21:16:35 by lmidori           #+#    #+#             */
/*   Updated: 2020/10/01 21:17:44 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char			**get_arg(t_list_args **list)
{
	char		**str;
	int			len_list;
	int			i;
	t_list_args	*tmp;

	tmp = *list;
	i = 0;
	if ((len_list = ft_lstsize_arg(tmp)) == 0)
		i++;
	if (!(str = (char**)malloc(sizeof(char*) * (len_list + i + 1))))
		return (NULL);
	if (len_list == 0)
	{
		str[len_list] = "";
		str[i] = NULL;
	}
	else
		str[len_list] = NULL;
	i = 0;
	while (tmp)
	{
		str[i++] = tmp->content;
		tmp = tmp->next;
	}
	return (str);
}
