/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_len_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 22:49:35 by lmidori           #+#    #+#             */
/*   Updated: 2020/10/10 21:25:14 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char		*skip_spaces(char *ptr)
{
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	return (ptr);
}

int			len_marks(char *ptr, char ch, int *len)
{
	int		i;

	i = 0;
	while (ptr[i] != ch && ptr[i] != '\0')
	{
		if (ptr[i] == '\\' && ch != '\'' &&
			(ptr[i + 1] == '\\' || ptr[i + 1] == '$'
			|| ptr[i + 1] == '`' || ptr[i + 1] == '\"'))
		{
			i += 2;
			*len += 1;
		}
		else
		{
			i++;
			*len += 1;
		}
	}
	if (ptr[i] == '\0')
		return (-2);
	return (i);
}

int			check_len_quotes_slash(int *i, char *ptr, int *len)
{
	int		tmp;

	tmp = 1;
	if (ptr[*i] == '\\')
	{
		if (ptr[*i + 1] == '\0')
			return (-1);
		(*i)++;
		(*len)++;
	}
	else if (ptr[*i] == '\"')
		tmp = len_marks(&ptr[++(*i)], '\"', len) + 1;
	else if (ptr[*i] == '\'')
		tmp = len_marks(&ptr[++(*i)], '\'', len) + 1;
	else if (tmp == 1)
		(*len)++;
	return (tmp);
}

int			len_arg(char *ptr)
{
	int		len;
	int		i;
	int		tmp;

	i = 0;
	len = 0;
	while (ptr[i] != ' ' && ptr[i] != '\0' && ptr[i] != '<'
		&& ptr[i] != '>' && ptr[i] != ';' && ptr[i] != '|')
	{
		tmp = 1;
		tmp = check_len_quotes_slash(&i, ptr, &len);
		if (tmp == -1)
		{
			ft_putstr_fd("Error: dquote\n", 1);
			return (-1);
		}
		i += tmp;
	}
	return (len);
}
