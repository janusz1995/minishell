
#include "parser.h"
#include "minishell.h"

void 		start_shell(t_all *all, t_head_struct *head_struct)
{
	char	**str;
	int		i;

	i = -1;
	str = get_arg(&(all->args));
	if (*str[0] == '\0' && all->spec == NULL) // leak
	{
		free(*str);
		free(str);
		return;
	}
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
	if (!arg && (head_struct->all.spec == NULL || *head_struct->all.spec != '|'))
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

long long		ft_atol_exit(const char *str)
{
	int				i;
	int				sign;
	double		number;
	long long	out;

	out = 0;
	i = 0;
	sign = 1;
	number = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (str[i] <= '9' && str[i] >= '0')
		number = number * 10 + (str[i++] - '0');
	if (number > 9223372036854775807)
	{
		return (256);
	}
	out = (long long)(number);
	if (sign == 1)
		out %= 256;
	else
		out = -(out % 256) + 256;
	return (out);
}

void		exit_cmd(char **str)
{
	int		i;
	int		minus;
	unsigned short code;
	minus = 0;
	i = 0;
	while (str[i] != NULL)
		i++;
	if (i == 1)
		exit(1);
	if (i != 2)
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 1);
	else
	{
		i = -1;
		if (str[1][0] =='-')
		{
			minus = 1;
			i++;
		}
		while (str[1][++i] != '\0')
			if (!ft_isdigit(str[1][i]))
			{
				i = 0;
				break;
			}
		if (i == 0)
		{
			ft_putstr_fd("exit\nminishell: exit: ", 1);
			ft_putstr_fd(str[1], 1);
			ft_putstr_fd(": numeric argument required\n", 1);
			exit (255);
		}
		else
		{
			if ((code = (unsigned short)ft_atol_exit(str[1])) == 256)
			{
				ft_putstr_fd("exit\nminishell: exit: ", 1);
				ft_putstr_fd(str[1], 1);
				ft_putstr_fd(": numeric argument required\n", 1);
				exit (255);
			}
			else
				exit (code);
		}
	}
	
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
	{
		exit_cmd(str);
	}
}



void		get_copy_all(t_all *all, t_all *copy_all, t_list_args *args)
{
	t_list_args	*tmp;
	t_all	*tmp_copy;

	tmp = args;
	tmp_copy = copy_all;
	tmp_copy->args = NULL;
	tmp_copy->spec = NULL;
	tmp_copy->equal = 0;

	tmp_copy->spec = ft_strdup(all->spec);
	while (tmp)
	{
		ft_lstadd_back_arg(&(copy_all->args), ft_lstnew_arg(ft_strdup(tmp->content), tmp->spec_flag));
		tmp = tmp->next;
	}
}

void 		redirect(t_head_struct *head_struct, char **str, t_list_args *args)
{
	int		fd;
//	int 	saveout;
	char	**save_all;

	save_all = NULL;
	if (head_struct->p_copy == NULL)
	{
		get_copy_all(&head_struct->all, &head_struct->copy_all, args);
		head_struct->p_copy = &head_struct->copy_all;
		head_struct->flag_redir = 1;
	}
	else if (head_struct->all.spec && ft_strncmp(head_struct->all.spec, ">>", 3) == 0)
	{
		if ((fd = open(str[0], O_CREAT | O_APPEND | O_WRONLY , 0644)) < 0)  //O_CREAT
		{

		}
		close(fd);
	}
	else if (head_struct->all.spec && *(head_struct->all.spec) == '>')
	{
		if ((fd = open(str[0], O_CREAT | O_WRONLY | O_TRUNC, 0644)) < 0)  //O_CREAT
		{
			// return error
		}
		close(fd);
	}
	else if (head_struct->all.spec && *(head_struct->all.spec) == '<')
	{
		if ((fd = open(str[0], O_RDONLY)) < 0)
		{

		}
		close(fd);
	}
	else
	{
		head_struct->flag_redir = 0;

		if (head_struct->copy_all.spec && *(head_struct->copy_all.spec) == '<')
		{
			if ((fd = open(str[0], O_RDONLY)) < 0)
			{

			}
		}
		else if (head_struct->copy_all.spec && ft_strncmp(head_struct->copy_all.spec, ">>", 3) == 0)
		{
			if ((fd = open(str[0], O_CREAT | O_APPEND | O_WRONLY , 0644)) < 0)	//O_CREAT;
			{

			}
		}
		else
		{
 			if ((fd = open(str[0], O_CREAT | O_WRONLY | O_TRUNC, 0644)) < 0)  //O_CREAT
			{
				//return error
			}
		}
		save_all = get_arg((&head_struct->copy_all.args));
		//saveout = dup(1);
		if (head_struct->copy_all.spec && *(head_struct->copy_all.spec) == '<')
			dup2(fd, 0);
		else
			dup2(fd, 1);
		if (head_struct->copy_all.args != NULL)
			select_cmd(head_struct, save_all, head_struct->copy_all.args);
		//dup2(saveout, 1);
		head_struct->p_copy = NULL;
		close(fd);
		//close(saveout);
	}
}

void 		select_cmd(t_head_struct *head_struct, char **str, t_list_args *args)
{
	pid_t	pid;
	pid_t	wait_pid;
	int		status;

	head_struct->flag_pipe = 0;
	if (head_struct->all.equal == 1)
		add_new_env(head_struct, str);
	else if (head_struct->all.spec && *(head_struct->all.spec) == '|')
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
	else if (head_struct->flag_redir || (head_struct->all.spec && (*(head_struct->all.spec) == '>' ||
			(ft_strncmp(head_struct->all.spec, ">>", 3) == 0) || *(head_struct->all.spec) == '<')))
	{
		if (head_struct->p_copy != NULL)
			ft_lstadd_back_arg(&head_struct->copy_all.args, args->next);
		redirect(head_struct, str, args);
	}
	else
	{
		if (check_cond(str[0]))
			select_cmd_two(head_struct, str, args, 1);
		else
			diff_cmd(head_struct, str);
	}
}