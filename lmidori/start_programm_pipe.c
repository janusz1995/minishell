/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_programm_pipe.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 13:48:15 by lmidori           #+#    #+#             */
/*   Updated: 2020/10/12 13:48:18 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int			start_programm_pipe(char *path_bin, char **env, char **cmd_arg)
{
	char	*tmp;
	int		status;
	int		flag;

	status = 0;
	tmp = init_full_path(path_bin, cmd_arg[0]);
	if ((flag = check_stat(cmd_arg, tmp)) != -1)
		return (flag);
	if (execve(tmp, cmd_arg, env) == -1)
	{
		if (ft_strchr(cmd_arg[0], '/') != NULL)
			error_directory_diff(cmd_arg[0]);
		else
			error_command_diff(cmd_arg[0]);
		exit(WEXITSTATUS(status));
	}
	return (WEXITSTATUS(status));
}
