/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 21:20:17 by lmidori           #+#    #+#             */
/*   Updated: 2020/10/05 23:27:56 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char		**path_bin(t_env **head)
{
	t_env	*tmp;
	char	**str;

	str = NULL;
	tmp = (*head);
	while (tmp->next != NULL)
	{
		if ((ft_strncmp(tmp->key_value[0], "PATH=",
			ft_strlen(tmp->key_value[0]))) == 0)
		{
			str = ft_split(tmp->key_value[1], ':');
			break ;
		}
		tmp = tmp->next;
	}
	return (str);
}
