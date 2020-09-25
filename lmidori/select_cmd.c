
#include "parser.h"
#include "minishell.h"

void 		start_shell(t_all *all, t_head_struct *head_struct)
{
	char	**str;

	str = get_arg(&(all->args));
	if (*str[0] == '\0') // leak
		return;
	select_cmd(head_struct, str, head_struct->all.args);
	free(str);
}

int			add_new_env(t_head_struct *head_struct, char **str)
{
	t_list_args *arg;
	int			flag;
	int			i;

	i = 0;
	flag = 1;
	arg = head_struct->all.args;
	while (arg && arg->spec_flag == 2)
	{
		if (!(flag = check_name(arg->content, '=')))
			break;
		arg = arg->next;
		i++;
	}
	if (!arg)
	{
		arg = head_struct->all.args;
		while (arg != NULL)
		{
			if (!(init_env(arg->content, &(head_struct->env))))
				return (-1);
			arg = arg->next;
		}
	}
	else if (!flag || arg->spec_flag != 2)
	{
		head_struct->all.equal = 0;
		select_cmd(head_struct, &str[i], arg);
	}
	return (1);
}

void 		select_cmd(t_head_struct *head_struct, char **str, t_list_args *args)
{
	pid_t	pid;
	pid_t	wait_pid;
	int		status;

	head_struct->flag_pipe = 0;
	if (head_struct->all.spec && *(head_struct->all.spec) == '|')
	{
		head_struct->flag_pipe = 1;
		pipe(head_struct->fd);
		pid = fork();
		if (pid == 0)
		{
			close(head_struct->fd[0]);
			dup2(head_struct->fd[1], 1);
			close(head_struct->fd[1]);
			if (check_cond(str[0]) == 1)
			{
				if (str[0] && (ft_strncmp(str[0], "cd", ft_strlen(str[0]) + 1) == 0))
					cmd_cd(str, head_struct->env);
				else if (str[0] && (ft_strncmp(str[0], "pwd", ft_strlen(str[0]) + 1)) == 0)
					cmd_pwd(head_struct->env);
				else if (str[0] && (ft_strncmp(str[0], "env", ft_strlen(str[0]) + 1) == 0))
					cmd_env(head_struct->env);
				else if (str[0] && (ft_strncmp(str[0], "unset", ft_strlen(str[0]) + 1) == 0))
					cmd_unset(&(head_struct->env), str[1]);
				else if (str[0] && (ft_strncmp(str[0], "export", ft_strlen(str[0]) + 1) == 0))
					cmd_export(&(head_struct->env), args);
				else if (str[0] && (ft_strncmp(str[0], "echo", ft_strlen(str[0]) + 1) == 0))
					cmd_echo(args);
				else if (str[0] && (ft_strncmp(str[0], "exit", ft_strlen(str[0]) + 1) == 0))
					exit(0);
				exit(0);
			}
			else
			{
				diff_cmd(head_struct, str);
				exit(0);
			}
		}
		else if (pid < 0)
		{
			perror("lsh");
		}
		else
		{
			close(head_struct->fd[1]);
			dup2(head_struct->fd[0], 0);
			close(head_struct->fd[0]);
			wait_pid = waitpid(pid, &status, WUNTRACED);
		}
	}
	else
	{
		if (head_struct->all.equal == 1)
			add_new_env(head_struct, str);
		else if (check_cond(str[0]))
		{
			if (str[0] && (ft_strncmp(str[0], "cd", ft_strlen(str[0]) + 1) == 0))
				cmd_cd(str, head_struct->env);
			else if (str[0] && (ft_strncmp(str[0], "pwd", ft_strlen(str[0]) + 1)) == 0)
				cmd_pwd(head_struct->env);
			else if (str[0] && (ft_strncmp(str[0], "env", ft_strlen(str[0]) + 1) == 0))
				cmd_env(head_struct->env);
			else if (str[0] && (ft_strncmp(str[0], "unset", ft_strlen(str[0]) + 1) == 0))
			{
				int i = 0;
				while (str[i])
					cmd_unset(&(head_struct->env), str[i++]);
			}
			else if (str[0] && (ft_strncmp(str[0], "export", ft_strlen(str[0]) + 1) == 0))
				cmd_export(&(head_struct->env), args);
			else if (str[0] && (ft_strncmp(str[0], "echo", ft_strlen(str[0]) + 1) == 0))
				cmd_echo(args);
			else if (str[0] && (ft_strncmp(str[0], "exit", ft_strlen(str[0]) + 1) == 0))
				exit(0);
		}
		else
			diff_cmd(head_struct, str);
	}
}