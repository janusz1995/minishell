/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_arg_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 21:55:02 by lmidori           #+#    #+#             */
/*   Updated: 2020/10/03 23:31:04 by lmidori          ###   ########.fr       */
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
	{
		ft_putstr_fd("Error: The memory could not be allocated\n", 1);
		exit(2);
	}
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
	if (str[i] == '?')
	{
		arg->arg = ft_itoa(error);
		return (1);
	}
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (-2);
	while (ft_isdigit(str[i]) || ft_isalpha(str[i]) || str[i] == '_')
		i++;
	len = i - 1;
	tmp1 = ft_substr(str, 1, len);
	tmp2 = get_arg_env(tmp1, env);
	str_concatenated(arg, tmp1, tmp2);
	i = ft_strlen(tmp1);
	free(tmp1);
	free(tmp2);
	return (i);
}
