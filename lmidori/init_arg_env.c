/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_arg_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 21:55:02 by lmidori           #+#    #+#             */
/*   Updated: 2020/09/18 21:55:39 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int			str_concatenated(t_arg *arg, char *tmp1, char *tmp2)
{
	int		i;
	int		j;
	int		len;
	char	*new_arg;
	
	len = arg->len - ft_strlen(tmp1) + ft_strlen(tmp2);
	if (!(new_arg = (char *)ft_calloc(sizeof(char), (len + 1))))
		return (-1);
	i = -1;
	while (arg->arg[++i] != '\0')
		new_arg[i] = arg->arg[i];
	j = -1;
	while (tmp2[++j] != '\0')
		new_arg[i++] = tmp2[j];
	free(arg->arg);
	arg->arg = new_arg;
	arg->len = len;
	arg->j = i;
	return (1);
}

int			init_arg_env(char *str, t_arg *arg, t_env *env)
{
	int		i;
	int		len;
	char	*tmp1;
	char	*tmp2;

	i = 1;
	while (ft_isdigit(str[i]) || ft_isalpha(str[i]))
		i++;
	len = i - 1;
	if (!(tmp1 = ft_substr(str, 1, len)))
		return (-1);
	if (!(tmp2 = get_arg_env(tmp1, env)))
		return (-1);
	if (str_concatenated(arg, tmp1, tmp2) == -1)
		return (-1);
	i = ft_strlen(tmp1);
	free(tmp1);
	free(tmp2);
	return (i);
}
