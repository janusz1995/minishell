/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_programm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 22:29:19 by lmidori           #+#    #+#             */
/*   Updated: 2020/10/09 23:25:17 by lmidori          ###   ########.fr       */
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

void		exec_error(int *status, char **cmd_arg, char **env, char *tmp)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if ((*status = execve(tmp, cmd_arg, env)) == -1)
	{
		if (ft_strchr(cmd_arg[0], '/') != NULL)
			error_directory_diff(cmd_arg[0]);
		else
			error_command_diff(cmd_arg[0]);
		exit(WTERMSIG(*status));
	}
}

int			exec_fork(char **cmd_arg, char **env, char *tmp)
{
	pid_t	wait_pid;
	int		status;

	if ((g_pid = fork()) < 0)
		error_fork();
	else if (g_pid == 0)
		exec_error(&status, cmd_arg, env, tmp);
	else
	{
		wait_pid = waitpid(g_pid, &status, WUNTRACED);
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == 2)
				g_error = 130;
			if (WTERMSIG(status) == 3)
				g_error = 131;
			write(1, "\n", 1);
		}
		else
			g_error = WEXITSTATUS(status);
		signal(SIGINT, sigint);
		signal(SIGQUIT, sigquit);
	}
	return (1);
}

int			start_programm(char *path_bin, char **env, char **cmd_arg)
{
	char	*tmp;
	int		flag;

	tmp = init_full_path(path_bin, cmd_arg[0]);
	if ((flag = check_stat(cmd_arg, tmp)) != -1)
		return (flag);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	exec_fork(cmd_arg, env, tmp);
	free(tmp);
	return (1);
}
