
#include "parser.h"

void 		start_programm(char *cmd, char *path_bin, char **env, char **cmd_arg)
{
	pid_t	pid;
	pid_t	wait_pid;
	char	*tmp;
	int		status;

	pid = fork();
	if (path_bin != NULL)
		tmp = ft_strjoin(path_bin, "/");
	tmp = ft_strjoin(tmp, cmd);
	if (pid == 0)
	{
		if (execve(tmp, cmd_arg, env) == -1)
		{
			ft_putstr_fd( "Error\n",2);
			exit (WEXITSTATUS(status));
		}
	}
	else if (pid < 0)
	{
		perror("lsh");
	}
	else
		wait_pid = waitpid(pid, &status, WUNTRACED);
}