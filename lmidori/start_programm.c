/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_programm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 22:29:19 by lmidori           #+#    #+#             */
/*   Updated: 2020/10/03 23:24:24 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void		start_programm_pipe(char *path_bin, char **env, char **cmd_arg)
{
	char	*tmp;
	int		status;

	if (path_bin != NULL)
		tmp = ft_strjoin(path_bin, "/");
	tmp = ft_strjoin(tmp, cmd_arg[0]);  // утечка
	if (execve(tmp, cmd_arg, env) == -1)
	{
		ft_putstr_fd( "Error start programm\n",2);
		exit (WEXITSTATUS(status));
	}
}

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

void 		start_programm(char *path_bin, char **env, char **cmd_arg)
{
	pid_t	pid;
	pid_t	wait_pid;
	char	*tmp;
	int		status;

	pid = fork();
	if (path_bin != NULL)
		tmp = ft_strjoin(path_bin, "/");
	tmp = ft_strjoin(tmp, cmd_arg[0]);  // утечка
	if (pid == 0)
	{
		if (execve(tmp, cmd_arg, env) == -1)
		{
			if (ft_strchr(cmd_arg[0], '/') != NULL)
				error_directory_diff(cmd_arg[0]);
			else
				error_command_diff(cmd_arg[0]);
			exit(WEXITSTATUS(status));
		}
	}
	else if (pid < 0)
		perror("lsh");
	else
	{
		wait_pid = waitpid(pid, &status, WUNTRACED);
		error = status;			// ???
		printf("%d\n", error);
	}
}
