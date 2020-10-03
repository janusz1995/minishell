/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 18:16:00 by lmidori           #+#    #+#             */
/*   Updated: 2020/10/03 18:25:16 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

long long			ft_atol_exit(const char *str)
{
	int				i;
	int				sign;
	double			number;
	long long		out;

	out = 0;
	i = 0;
	sign = 1;
	number = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (str[i] <= '9' && str[i] >= '0')
		number = number * 10 + (str[i++] - '0');
	if (number > 9223372036854775807)
		return (256);
	out = (long long)(number);
	if (sign == 1)
		out %= 256;
	else
		out = -(out % 256) + 256;
	return (out);
}

void				error_exit(char **str)
{
	ft_putstr_fd("exit\nminishell: exit: ", 1);
	ft_putstr_fd(str[1], 1);
	ft_putstr_fd(": numeric argument required\n", 1);
	exit(255);
}

int					check_args_exit(char **str)
{
	int				i;

	i = 0;
	while (str[i] != NULL)
		i++;
	if (i == 1)
		exit(0);
	if (i != 2)
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 1);
		error = 1;
		return (0);
	}
	return (1);
}

void				exit_cmd(char **str)
{
	int				i;
	unsigned short	code;

	error = 0;
	i = -1;
	if (!check_args_exit(str))
		return ;
	if (str[1][0] == '-' || str[1][0] == '+')
		i++;
	while (str[1][++i] != '\0')
		if (!ft_isdigit(str[1][i]))
			error_exit(str);
	if ((code = (unsigned short)ft_atol_exit(str[1])) == 256)
		error_exit(str);
	else
	{
		error = code;
		exit(code);
	}
}
