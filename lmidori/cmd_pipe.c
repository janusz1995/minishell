
#include "parser.h"

void	cmd_pipe(t_head_struct *head_struct, char **str, t_list_args *args, int flag_dup)
{
	pid_t			pid;
	pid_t			wait_pid;
	int				status;

	head_struct->flag_pipe = 1;
	pipe(head_struct->fd);
	pid = fork();
	if (pid == 0)
	{
		close(head_struct->fd[0]);
		dup2(head_struct->fd[1], 1);
		close(head_struct->fd[1]);
		if (flag_dup)
			dup2(head_struct->fd_redir, 1);
		commands(head_struct, str, args);
		exit(0);
	}
	else if (pid < 0)
		perror("lsh");
	else
	{
		close(head_struct->fd[1]);
		dup2(head_struct->fd[0], 0);
		close(head_struct->fd[0]);
		wait_pid = waitpid(pid, &status, WUNTRACED);
	}
}
