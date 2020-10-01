/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redact_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 23:00:05 by lmidori           #+#    #+#             */
/*   Updated: 2020/10/01 23:00:22 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int			redact_env(t_env **envp, char *name, char *value)
{
	t_env	*tmp;

	tmp = *envp;
	while (tmp)
	{
		if (ft_strncmp(tmp->key_value[0], name,
			ft_strlen(tmp->key_value[0]) + 1) == 0)
		{
			tmp->visible = 1;
			if (value != NULL)
				tmp->key_value[1] = ft_strdup(value);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
