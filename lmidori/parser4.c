/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 12:03:05 by lmidori           #+#    #+#             */
/*   Updated: 2020/09/17 19:24:07 by lmidori          ###   ########.fr       */
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
			if ((ft_strncmp(env->key_value[0], tmp, ft_strlen(env->key_value[0]))) == 0)
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

void		ft_init_struct(t_all *all)
{
	all->cmd = NULL;
	all->args = NULL;
	all->spec = NULL;
}

void			fool_strcut(t_all *all, t_list_args **list)
{
	t_list_args *tmp;

	tmp = *list;
	if (tmp)
	{
		ft_init_struct(all);
		all->cmd = tmp->content;
		tmp = tmp->next;
		while (tmp && !tmp->spec_flag)
		{
			ft_lstadd_back_arg(&(all->args), ft_lstnew_arg(tmp->content, 0));
			tmp = tmp->next;
		}
		if (tmp && tmp->spec_flag)
		{
			all->spec = tmp->content;
			tmp = tmp->next;
		}
	}
	*list = tmp;
}

void		ft_clear_strcut(t_all *all)
{
	if (all->cmd != NULL)
		free(all->cmd);
	all->cmd = NULL;
	if (all->spec != NULL)
		free(all->spec);
	all->spec = NULL;
	ft_lstclear_args(&(all->args), free);
	// free(all);
}

int			parser(char *str, t_arg *arg, t_list_args **list, t_env *env)
{
	int		tmp;
	int		len;
	t_all	all;

	while (*str)
	{
		if (*(str = skip_spaces(str)) == '\0')
			break;
		while (*str == '>' || *str == '<' || *str == ';' || *str == '|')
		{
			if ((tmp = read_special_char(str, list)) == -1)
				return (-1);
			str += tmp;
			fool_strcut(&all, list);
			ft_lst_print(all.args);
			//DRINA_FUNC_GO(&all); // GGOOG!
			//ft_clear_strcut(&all);
			ft_lst_print(all.args);
		}
		if (*(str = skip_spaces(str)) == '\0')
			break;
		len = len_arg(str);
		if (!init_struct(arg, len))
			return (-1);
		if ((tmp = read_arg(str, arg, env, list)) == -1)
			return (-1);
		str += tmp;
	}
	fool_strcut(&all, list);
	ft_lst_print(all.args);
	//DRINA_FUNC_GO(&all); //GOGOGOG
	ft_clear_strcut(&all);
	ft_lst_print(all.args);

	return (1);
}


