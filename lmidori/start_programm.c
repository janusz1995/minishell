/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_programm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 22:29:19 by lmidori           #+#    #+#             */
/*   Updated: 2020/10/05 22:48:59 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char		*init_full_path(char *path_bin, char *cmd_arg)
{
	char	*tmp;
	char	*ptr;

	tmp = NULL;
	if (path_bin != NULL)
		tmp = ft_strjoin(path_bin, "/");
	ptr = tmp;
	tmp = ft_strjoin(tmp, cmd_arg);
	if (ptr != NULL)
		free(ptr);
	return (tmp);
}

void		start_programm_pipe(char *path_bin, char **env, char **cmd_arg)
{
	char	*tmp;
	int		status;

	tmp = init_full_path(path_bin, cmd_arg[0]);
	if (execve(tmp, cmd_arg, env) == -1)
	{
		if (ft_strchr(cmd_arg[0], '/') != NULL)
			error_directory_diff(cmd_arg[0]);
		else
			error_command_diff(cmd_arg[0]);
		exit(WEXITSTATUS(status));
	}
}

void		start_programm(char *path_bin, char **env, char **cmd_arg)
{
	pid_t	pid;
	pid_t	wait_pid;
	char	*tmp;
	int		status;

	tmp = init_full_path(path_bin, cmd_arg[0]);
	if ((pid = fork()) < 0)
		error_fork();
	else if (pid == 0)
	{
		if ((status = execve(tmp, cmd_arg, env)) == -1)
		{
			if (ft_strchr(cmd_arg[0], '/') != NULL)
				error_directory_diff(cmd_arg[0]);
			else
				error_command_diff(cmd_arg[0]);
			exit(WEXITSTATUS(status));
		}
	}
	else
	{
		wait_pid = waitpid(pid, &status, WUNTRACED);
		error = WEXITSTATUS(status);
	}
	free(tmp);
}
