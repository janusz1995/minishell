/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_programm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 22:29:19 by lmidori           #+#    #+#             */
/*   Updated: 2020/10/10 23:08:00 by lmidori          ###   ########.fr       */
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

int			check_stat(char **cmd_arg, char *tmp)
{
	struct stat st;

	stat(tmp, &st);
	if (!(S_ISREG(st.st_mode) == 1 && (st.st_mode & S_IXUSR)))
	{
		if (!(S_ISREG(st.st_mode)))
		{
			free(tmp);
			return (0);
		}
		if (!(st.st_mode & S_IXUSR))
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(cmd_arg[0], 2);
			ft_putstr_fd(": Permission denied\n", 2);
			g_error = 126;
			free(tmp);
			return (1);
		}
		free(tmp);
		return (0);
	}
	return (-1);
}

int			exec_fork(char **cmd_arg, char **env, char *tmp)
{
	pid_t	wait_pid;
	int		status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if ((g_pid = fork()) < 0)
		error_fork();
	else if (g_pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
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
		wait_pid = waitpid(g_pid, &status, WUNTRACED);
		signal(SIGINT, sigint);
		signal(SIGQUIT, sigquit);
		g_error = WEXITSTATUS(status);
	}
	return (1);
}

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

int			start_programm(char *path_bin, char **env, char **cmd_arg)
{
	char	*tmp;
	int		flag;

	tmp = init_full_path(path_bin, cmd_arg[0]);
	if ((flag = check_stat(cmd_arg, tmp)) != -1)
		return (flag);
	exec_fork(cmd_arg, env, tmp);
	free(tmp);
	return (1);
}
