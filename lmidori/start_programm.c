
#include "parser.h"

void 		start_programm(t_head_struct *head_struct, char *path_bin, char **env, char **cmd_arg)
{
	pid_t	pid;
	pid_t	wait_pid;
	char	*tmp;
	int		status;
	int		pfildes[2];

	if (head_struct->all.spec && *(head_struct->all.spec) == '|')
		pipe(pfildes);
	pid = fork();
	if (path_bin != NULL)
		tmp = ft_strjoin(path_bin, "/");
	tmp = ft_strjoin(tmp, cmd_arg[0]);  // утечка
	if (pid == 0)
	{
		if (head_struct->all.spec && *(head_struct->all.spec) == '|')
		{
			close(pfildes[0]);
			dup2(pfildes[1], 1);
			close(pfildes[1]);
		}
		if (execve(tmp, cmd_arg, env) == -1)
		{
			ft_putstr_fd( "Error start programm\n",2);
			exit (WEXITSTATUS(status));
		}
	}
	else if (pid < 0)
	{
		perror("lsh");
	}
	else
	{
		if (head_struct->all.spec && *(head_struct->all.spec) == '|')
		{
			close(pfildes[1]);
			dup2(pfildes[0], 0);
			close(pfildes[0]);
		}
		wait_pid = waitpid(pid, &status, WUNTRACED);
	}
}
