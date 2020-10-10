/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 19:35:01 by lmidori           #+#    #+#             */
/*   Updated: 2020/10/10 17:38:11 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int			skip_quote(char *str, char ch)
{
	int		i;

	i = 1;
	while (str[i] != '\0' && str[i] != ch)
	{
		if (str[i] == '\\' && ch != '\'' &&
			(str[i + 1] == '\\' || str[i + 1] == '$'
			|| str[i + 1] == '`' || str[i + 1] == '\"'))
			i += 2;
		else
			i++;
	}
	if (str[i] == '\0')
		return (-2);
	return (i);
}

int			skip_quotes(char *str)
{
	int		i;
	int		tmp;

	tmp = 1;
	i = 0;
	if (str[i] == '\\')
	{
		if (str[i + 1] == '\0')
			return (-1);
		i += 2;
		tmp++;
	}
	else if (str[i] == '\'')
		tmp += skip_quote(&str[i], '\'');
	else if (str[i] == '\"')
		tmp += skip_quote(&str[i], '\"');
	return (tmp);
}

int			find_spec(char *str, char *spec)
{
	int		i;
	int		tmp;

	i = 0;
	while (str[i] != '\0' && !ft_strchr("<>|;", str[i]))
	{
		tmp = 1;
		if ((tmp = skip_quotes(&str[i])) == -1)
		{
			ft_putstr_fd("Error: dquote\n", 1);
			return (-1);
		}
		i += tmp;
	}
	if (str[i] == '\0')
		return (i);
	spec[0] = str[i];
	if (spec[0] == str[i + 1] && spec[0] != '>')
		return (-1);
	if (spec[0] == '>' && str[i + 1] == '>')
	{
		spec[1] = '>';
		i++;
	}
	return (i);
}

int			check_right(char *str, char *spec, int *iter)
{
	int		i;
	int		tmp;
	char	ch;

	i = 1;
	tmp = 0;
	ch = *skip_spaces(&str[i]);
	if (ch == '\0')
		return (0);
	if (ft_strchr("<>;|", ch) != NULL)
	{
		if (spec[0] == '|' && (ch == '>' || ch == '<'))
		{
			*iter += len_spaces(&str[i]);
			return (1);
		}
		else
			return (-1);
	}
	return (1);
}
