/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 12:03:05 by lmidori           #+#    #+#             */
/*   Updated: 2020/09/18 21:55:24 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"







int			read_special_char(char *str, t_list_args **list)
{
	char	*out;
	int		i;

	i = 0;
	if (str[i] == '>' && str[i + 1] == '>')
	{
		if ((out = (char *)malloc(sizeof(char) * 3)) == NULL)
			return (-1);
		out[0] = '>';
		out[1] = '>';
		out[2] = '\0';
	}
	else
	{
		if ((out = (char *)malloc(sizeof(char) * 2)) == NULL)
			return (-1);
		out[0] = *str;
		out[1] = '\0';
	}
	ft_lstadd_back_arg(list, ft_lstnew_arg(out, 1));
	if (!(*list))
		return (-1);
	return (ft_strlen(out));
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
			//DRINA_FUNC_GO(&all); // GGOOG!
			ft_clear_strcut(&all);
		}
		if (*(str = skip_spaces(str)) == '\0')
			break;
		len = len_arg(str);
		if (init_struct(arg, len) == -1)
			return (-1);
		if ((tmp = read_arg(str, arg, env, list)) == -1)
			return (-1);
		str += tmp;
	}
	fool_strcut(&all, list);
	//DRINA_FUNC_GO(&all); //GOGOGOG
	ft_clear_strcut(&all);

	return (1);
}


