/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_spec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 16:48:25 by lmidori           #+#    #+#             */
/*   Updated: 2020/10/09 20:14:39 by lmidori          ###   ########.fr       */
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

int			len_spaces(char *str)
{
	int		i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	return (i);
}

int			check_special(char *str, char *spec, int *i)
{
	int		left;
	int		right;
	int		tmp;

	left = 0;
	right = 0;
	if ((tmp = find_spec(&str[*i], spec)) == -1)
		return (0);
	if (spec[0] == '\0' || str[*i + tmp] == '\0')
		return (1);
	if (*skip_spaces(&str[*i]) != spec[0])
		left = 1;
	*i += tmp;
	if ((spec[0] == ';' || spec[0] == '|') && !left)
		return (0);
	right = check_right(&str[*i], spec, i);
	if (!right && spec[0] == ';')
		return (1);
	if ((!right && (spec[0] == '>' || spec[0] == '<'
		|| spec[0] == '|')) || right == -1)
		return (0);
	return (2);
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
		if ((tmp = check_special(str, spec, &i)) == 0)
			break ;
		if (tmp == 1)
			return (1);
	}
	error_spec(spec);
	return (0);
}
