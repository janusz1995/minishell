/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 22:52:29 by lmidori           #+#    #+#             */
/*   Updated: 2020/10/01 18:19:31 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int			init_arg_quotes(char *str, t_arg *arg, t_env *env)
{
	int		i;
	char	ch;
	int		tmp;

	i = 0;
	ch = str[i];
	while (str[++i] != ch && str[i] != '\0')
	{
		if (str[i] == '\\' && ch != '\'' && ft_strchr("\\\"$`", str[i + 1]) != NULL)
			arg->arg[arg->j++] = str[++i];
		else if (str[i] == '$' && ch != '\'')
		{
			if ((tmp = init_arg_env(&str[i], arg, env)) == -1)
				return (-1);
			if (tmp == -2)
				arg->arg[arg->j++] = str[i];
			else
				i += tmp;
		}
		else
			arg->arg[arg->j++] = str[i];
	}
	if (str[i] == '\0')
		return (-1);
	return (i);
}

int			init_tilde(char *str, t_arg *arg, t_env *env)
{
	int		i;
	int		len;
	char	*home;

	if (!(home = get_home_dir(env)))
		return (-1);
	len = ft_strlen(home);
	i = -1;
	if (str[1] != '/')
	{
		free(arg->arg);
		arg->arg = home;
	}
	else
	{
		len = arg->len + ft_strlen(home) - 1;
		arg->len = len;
		free(arg->arg);
		if (!(arg->arg = (char *)malloc(sizeof(char) * (len + 1))))
			return (-1);
		arg->arg[len] = '\0';
		while (home[++i] != '\0')
			arg->arg[i] = home[i];
		arg->j = i;
	}
	return (1);
}

int			init_quotes_slash(char *str, int *i, t_arg *arg, t_env *env)
{
	int		tmp;
	int		flag;

	flag = 0;
	if (str[*i] == '\\')
		arg->arg[arg->j++] = str[++(*i)];
	else if (str[*i] == '\"' || str[*i] == '\'')
	{
		if ((tmp = init_arg_quotes(&str[*i], arg, env)) == -1)
			return (-1);
		*i += tmp;
	}
	else if (str[*i] == '$')
	{
		if ((tmp = init_arg_env(&str[*i], arg, env)) == -1)
			return (-1);
		*i += tmp;
	}
	else
	{
		if (str[*i] == '=' && i != 0 && (ft_isdigit(str[*i - 1]) || ft_isalpha(str[*i - 1]) || str[*i - 1] == '_'))
			flag = 2;
		arg->arg[arg->j++] = str[*i];
	}
	return (flag);
}

int			read_arg(char *str, t_arg *arg, t_env *env, t_list_args **list)
{
	int		i;
	int		tmp;
	int		flag;
	int		tmp2;

	if (arg->len == -1 || !str)
		return (-1);
	i = -1;
	flag = 0;
	if (str[0] == '~' && (str[1] == '/' || str[1] == ' ' || str[1] == '\0'))
	{
		if ((tmp = init_tilde(str, arg, env)) == -1)
			return (-1);
		i += tmp;
	}
	while (ft_strchr(" ><;|\0", str[++i]) == NULL)
	{
		if ((tmp2 = init_quotes_slash(str, &i, arg, env)) == -1)
			return (-1);
		if (tmp2 == 2)
			flag = tmp2;
	}
	ft_lstadd_back_arg(list, ft_lstnew_arg(arg->arg, flag));
	if (!list)
		return (-1);
	return (i);
}
