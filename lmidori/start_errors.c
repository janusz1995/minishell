/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 17:04:34 by lmidori           #+#    #+#             */
/*   Updated: 2020/10/05 18:59:09 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void		error_directory_diff(char *dir)
{
	DIR		*flow;

	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(dir, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	if ((flow = opendir(dir)) != NULL)
	{
		error = 126;
		closedir(flow);
	}
	else
		error = 127;
}

void		error_command_diff(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	error = 127;
}

void		error_fork(void)
{
	char	*str;

	error = errno;
	str = strerror(errno);
	ft_putstr_fd("minishell: ", 2);
	ft_putendl_fd(str, 2);
	return ;
}
