/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 12:03:05 by lmidori           #+#    #+#             */
/*   Updated: 2020/10/01 22:20:50 by lmidori          ###   ########.fr       */
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
	while (*str)
	{
		if (*(str = skip_spaces(str)) == '\0')
			break ;
		while (*str == '>' || *str == '<' || *str == ';' || *str == '|')
		{
			if ((tmp = read_special_char(str, &(head_struct->list))) == -1)
				return (-1);
			str += tmp;
			fool_strcut(&(head_struct->all), &(head_struct->list));
			start_shell(&(head_struct->all), head_struct);
			ft_clear_strcut(&(head_struct->all));
		}
		if (*(str = skip_spaces(str)) == '\0')
			break ;
		len = len_arg(str);
		if (init_struct(arg, len) == -1)
			return (-1);
		if ((tmp = read_arg(str, arg, head_struct->env,
			&(head_struct->list))) == -1)
			return (-1);
		str += tmp;
	}
	fool_strcut(&(head_struct->all), &(head_struct->list));
	start_shell(&(head_struct->all), head_struct);
	ft_clear_strcut(&(head_struct->all));
	return (1);
}
