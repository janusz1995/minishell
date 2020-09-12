/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 22:52:29 by lmidori           #+#    #+#             */
/*   Updated: 2020/09/12 22:53:18 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			init_arg_marks(char *ptr, char *arg, char ch, int *j)
{
	int		i;

	i = 0;
	while (ptr[i] != ch && ptr[i] != '\0')
	{
		if (ptr[i] == '\\' && ch != '\'' && 
			(ptr[i + 1] == '\\' || ptr[i + 1] == '$'
			|| ptr[i + 1] == '`' || ptr[i + 1] == '\'' || ptr[i] == '\"'))
		{
			arg[*j] = ptr[i + 1];
			*j += 1;
			i += 2;
		}
		else
		{
			arg[*j] = ptr[i];
			*j += 1;
			i++;
		}
	}
	if (ptr[i] == '\0')
		return (-1);
	return (i);
}

int			read_args(char *ptr, int len, t_list_args **list)
{
	int		i;
	char	*out;
	int		j;
	int		tmp;
	char	ch;

	i = -1;
	j = 0;
	if (!ptr || *ptr == '\0' || len == -1)
		return (-1);
	if (!(out = (char *)malloc((len + 1) * sizeof(char))))
		return (-1);
	out[len] = '\0';
	while (ptr[++i] != ' ' && ptr[i] != '\0' && ptr[i] != '>'
		&& ptr[i] != '<' && ptr[i] != ';' && ptr[i] != '|')
	{
		if (ptr[i] == '\\')
			out[j++] = ptr[++i];
		else if (ptr[i] == '\"' || ptr[i] == '\'')
		{
			ch = ptr[i];
			if ((tmp = init_arg_marks(&ptr[++i], out, ch, &j)) == -1)
			{
				free(out);
				return (-1);
			}
			i += tmp;
		}
		else
			out[j++] = ptr[i];
	}
	ft_lstadd_back_arg(list, ft_lstnew_arg(out, 0));
	if (!list)
		return (-1);
	return (i);
}

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
	return (ft_strlen(out));
}
