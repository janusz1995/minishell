/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 12:03:05 by lmidori           #+#    #+#             */
/*   Updated: 2020/10/10 13:45:20 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int			read_special_char(char *str, t_list_args **list)
{
	char	*out;
	int		i;

	i = 0;
	if (str[i] == '>' && str[i + 1] == '>')
	{
		out = (char *)xmalloc(sizeof(char) * 3);
		out[0] = '>';
		out[1] = '>';
		out[2] = '\0';
	}
	else
	{
		out = (char *)xmalloc(sizeof(char) * 2);
		out[0] = *str;
		out[1] = '\0';
	}
	ft_lstadd_back_arg(list, ft_lstnew_arg(out, 1));
	return (ft_strlen(out));
}

void		init_head_struct(t_head_struct *head_struct)
{
	head_struct->all.args = NULL;
	head_struct->list = NULL;
}

int			parser(char *str, t_arg *arg, t_head_struct *head_struct)
{
	int		tmp;
	int		len;

	init_head_struct(head_struct);
	if (*str != '\0' && !check_double_spec(str))
	{
		return (-1);
	}
	while (*str)
	{
		if (*(str = skip_spaces(str)) == '\0')
			break ;
		while (*str == '>' || *str == '<' || *str == ';' || *str == '|')
		{
			tmp = read_special_char(str, &(head_struct->list));
			str += tmp;
			fool_strcut(&(head_struct->all), &(head_struct->list));
			start_shell(&(head_struct->all), head_struct);
			if (head_struct->all.spec && *head_struct->all.spec == ';')
			{
				dup2(head_struct->saveinput, 0);
				dup2(head_struct->saveoutput, 1);
			}
			ft_clear_strcut(&(head_struct->all));
		}
		if (*(str = skip_spaces(str)) == '\0')
			break ;
		if ((len = len_arg(str)) == -1)
			return (-1); // ??? clearing
		init_struct(arg, len);
		if ((tmp = read_arg(str, arg, head_struct->env,
			&(head_struct->list))) == -1)
			return (-1);
		str += tmp;
	}
	fool_strcut(&(head_struct->all), &(head_struct->list));
	start_shell(&(head_struct->all), head_struct);
	ft_clear_strcut(&(head_struct->all));
	head_struct->flag_error = 0;

	return (1);
}
