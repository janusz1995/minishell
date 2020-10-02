/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 21:46:02 by lmidori           #+#    #+#             */
/*   Updated: 2020/10/02 23:12:50 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int			env_size(t_env *env)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = env;
	while (tmp != NULL)
	{
		if (tmp->visible != 0)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

void		sort_array(char **str, int len)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (i < len)
	{
		j = 0;
		while (j < len - 1)
		{
			if (ft_strncmp(str[j], str[j + 1], ft_strlen(str[j]) + 1) > 0)
			{
				tmp = str[j + 1];
				str[j + 1] = str[j];
				str[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

char		**creat_array(t_env **env)
{
	char	**str;
	t_env	*tmp;
	int		len;
	int		i;

	i = 0;
	tmp = *env;
	len = env_size(tmp);
	str = (char **)xmalloc(sizeof(char *) * (len + 1));
	str[len] = NULL;
	i = 0;
	while (i < len)
	{
		if (tmp->visible != 0)
			str[i] = ft_strdup(tmp->key_value[0]);
		i++;
		tmp = tmp->next;
	}
	sort_array(str, len);
	return (str);
}

void		print_vatible(t_env *tmp)
{
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(tmp->key_value[0], 1);
	if (tmp->key_value[1] != NULL)
	{
		ft_putstr_fd("=", 1);
		ft_putstr_fd("\"", 1);
		ft_putstr_fd(tmp->key_value[1], 1);
		ft_putstr_fd("\"", 1);
	}
	ft_putstr_fd("\n", 1);
}

void		print_export(t_env **env)
{
	t_env	*tmp;
	char	**str;
	int		i;

	tmp = *env;
	str = creat_array(env);
	i = -1;
	while (str[++i] != NULL)
	{
		tmp = *env;
		while (tmp)
		{
			if (ft_strncmp(str[i], tmp->key_value[0],
				ft_strlen(str[i]) + 1) == 0)
				print_vatible(tmp);
			tmp = tmp->next;
		}
		free(str[i]);
	}
	free(str);
	error = 0;
}
