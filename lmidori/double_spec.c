/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_spec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 16:48:25 by lmidori           #+#    #+#             */
/*   Updated: 2020/10/08 23:29:36 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void		error_spec(char *spec)
{
	ft_putstr_fd("minishell: syntax error\n", 2);
	free(spec);
	g_error = 258;
	return ;
}

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
		return (-1);
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
		tmp = skip_quotes(&str[i]);
		if (tmp == -1)
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
	{
		error_spec(spec);
		return (-1);
	}
	if (spec[0] == '>' && str[i + 1] == '>')
		spec[1] = '>';
	return (i);
}

int			check_double_spec(char *str)
{
	int		i;
	int		right;
	int		left;
	char	*spec;
	int		tmp;

	spec = (char *)ft_calloc(3, sizeof(char));
	right = 0;
	left = 0;
	i = -1;
	while (str[++i] != '\0')
	{
		if ((tmp = find_spec(&str[i], spec)) == -1)
			return (0);
		if (spec == '\0')
			return (1);
		if (*skip_spaces(&str[i]) != spec[0])
		{
			left = 1;
		}
		i += tmp;
		if ((spec[0] == ';' || spec[0] == '|') && !left)
		{
			error_spec(spec);
			return (0);
		}
		

	}
	return (1);
	
}