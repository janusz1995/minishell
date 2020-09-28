
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

void		select_cmd_two(t_head_struct *head_struct, char **str, t_list_args *args, int flag)
{
	int i;

	i = 0;
	if (str[0] && (ft_strncmp(str[0], "cd", ft_strlen(str[0]) + 1) == 0))
		cmd_cd(str, head_struct->env);
	else if (str[0] && (ft_strncmp(str[0], "pwd", ft_strlen(str[0]) + 1)) == 0)
		cmd_pwd(head_struct->env);
	else if (str[0] && (ft_strncmp(str[0], "env", ft_strlen(str[0]) + 1) == 0))
		cmd_env(head_struct->env);
	else if (str[0] && (ft_strncmp(str[0], "unset", ft_strlen(str[0]) + 1) == 0))
	{
		if (flag)
		{
			while (str[i])
				cmd_unset(&(head_struct->env), str[i++]);
		}
		else
			cmd_unset(&(head_struct->env), str[1]);
	}
	else if (str[0] && (ft_strncmp(str[0], "export", ft_strlen(str[0]) + 1) == 0))
		cmd_export(&(head_struct->env), args);
	else if (str[0] && (ft_strncmp(str[0], "echo", ft_strlen(str[0]) + 1) == 0))
		cmd_echo(args);
	else if (str[0] && (ft_strncmp(str[0], "exit", ft_strlen(str[0]) + 1) == 0))
		exit(0);
}

void		get_copy_all(t_all *all, t_all *copy_all)
{
	t_all	*tmp;
	t_all	*tmp_copy;

	tmp = all;
	tmp_copy = copy_all;
	tmp_copy->args = NULL;
	tmp_copy->spec = NULL;
	tmp_copy->equal = 0;
	while (tmp->args)
	{
		ft_lstadd_back_arg(&(copy_all->args), ft_lstnew_arg(ft_strdup(tmp->args->content), tmp->args->spec_flag));
		tmp->args = tmp->args->next;
	}
}

void 		redirect(t_head_struct *head_struct, char **str)
{
	int		fd;
	int 	saveout;
	char	**save_all;

	save_all = NULL;
	if (head_struct->p_copy == NULL)
	{
		get_copy_all(&head_struct->all, &head_struct->copy_all);
		head_struct->p_copy = &head_struct->copy_all;
		head_struct->flag_redir = 1;
	}
	else if (head_struct->all.spec && *(head_struct->all.spec) == '>')
	{
		if ((fd = open(head_struct->list->content, O_WRONLY)) < 0)  //O_CREAT
		{
			//return error
		}
	}
	else
	{
		head_struct->flag_redir = 0;
		if ((fd = open(str[0], O_CREAT | O_WRONLY , 0644)) < 0)  //O_CREAT
		{
			//return error
		}
		save_all = get_arg((&head_struct->copy_all.args));
		saveout = dup(1);
		dup2(fd, 1);
		select_cmd(head_struct, save_all, head_struct->copy_all.args);
		dup2(saveout, 1);
		head_struct->p_copy = NULL;
		close(fd);
		close(saveout);
	}
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
				select_cmd_two(head_struct, str, args, 0);
			else
				diff_cmd(head_struct, str);
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
	else if (head_struct->flag_redir || (head_struct->all.spec && *(head_struct->all.spec) == '>'))
	{
		redirect(head_struct, str);
	}
	else
	{
		if (head_struct->all.equal == 1)
			add_new_env(head_struct, str);
		else if (check_cond(str[0]))
			select_cmd_two(head_struct, str, args, 1);
		else
			diff_cmd(head_struct, str);
	}
}