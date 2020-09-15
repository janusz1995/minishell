/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 12:03:05 by lmidori           #+#    #+#             */
/*   Updated: 2020/09/15 21:26:19 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			init_struct(t_arg *arg, int len)
{
	if (len == -1)
		return (0);
	arg->len = len;
	if ((arg->arg = (char *)ft_calloc(sizeof(char), (len + 1))) == NULL)
		return (0);
	arg->arg[len] = '\0';
	arg->j = 0;
	return (1);
}

char		*get_arg_env(char *tmp, t_env *env)
{
	char	*out;
	char	*value;

	out = NULL;
	value = "";
	if (*tmp != '\0')
		while (env)
		{
			if ((ft_strncmp(env->key_value[0], tmp, ft_strlen(tmp))) == 0)
			{
				value = env->key_value[1];
				break;
			}
			env = env->next;
		}
	out = ft_strdup(value);
	return (out);
}

int			str_concatenated(t_arg *arg, char *tmp1, char *tmp2)
{
	int		i;
	int		j;
	int		len;
	char	*new_arg;
	
	len = arg->len - ft_strlen(tmp1) + ft_strlen(tmp2);
	if (!(new_arg = (char *)ft_calloc(sizeof(char), (len + 1))))
		return (0);
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
		return (0);
	if (!(tmp2 = get_arg_env(tmp1, env)))
		return (0);
	if (!str_concatenated(arg, tmp1, tmp2))
		return (0);
	i = ft_strlen(tmp1);
	free(tmp1);
	free(tmp2);
	return (i);
}

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
				return (0);
			i += tmp;
		}
		else
			arg->arg[arg->j++] = str[i];
	}
	if (str[i] == '\0')
		return (-1);
	return (i);
}

int			read_arg(char *str, t_arg *arg, t_env *env, t_list_args **list)
{
	int		i;
	int		tmp;
	int		flag;

	if (arg->len == -1 || !str)
		return (0);
	i = -1;
	flag = 0;
	while (ft_strchr(" ><;|\0", str[++i]) == NULL)
	{
		if (str[i] == '\\')
			arg->arg[arg->j++] = str[++i];
		else if (str[i] == '\"' || str[i] == '\'')
		{
			if ((tmp = init_arg_quotes(&str[i], arg, env)) == -1)
				return (-1);
			i += tmp;
		}
		else if (str[i] == '$')
		{
			if ((tmp = init_arg_env(&str[i], arg, env)) == -1)
				return (-1);
			i += tmp;
		}
		else
		{
			if (str[i] == '=' && i != 0 && (ft_isdigit(str[i - 1]) || ft_isalpha(str[i - 1])))
				flag = 1;
			arg->arg[arg->j++] = str[i];
		}
	}
	ft_lstadd_back_arg(list, ft_lstnew_arg(arg->arg, flag));
	if (!list)
		return (-1);
	return (i);
}

int			parser(char *str, t_arg *arg, t_list_args **list, t_env *env)
{
	int		tmp;
	int		len;

	while (*str)
	{
		if (*(str = skip_spaces(str)) == '\0')
			return (1);
		while (*str == '>' || *str == '<' || *str == ';' || *str == '|')
		{
			if ((tmp = read_special_char(str, list)) == -1)
				return (-1);
			str += tmp;
		}
		if (*(str = skip_spaces(str)) == '\0')
			return (1);
		len = len_arg(str);
		if (!init_struct(arg, len))
			return (-1);
		if ((tmp = read_arg(str, arg, env, list)) == -1)
			return (-1);
		str += tmp;
	}
	return (1);
}


