
#include "parser.h"
#include "minishell.h"

int		ft_lstsize_arg(t_list_args *lst)
{
	int	count;

	count = 0;
	while (lst != NULL)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

char		**get_arg(t_list_args **list)
{
	char	**str;
	int 	len_list;
	int		i;
	t_list_args *tmp;
	tmp = *list;
	i = 0;

	if ((len_list = ft_lstsize_arg(tmp)) == 0)
		i++;
	if (!(str = (char**)malloc(sizeof(char*) * (len_list + i + 1))))
		return (NULL);
	if (len_list == 0)
	{
		str[len_list] = "";
		str[i] = NULL;
	}
	else
		str[len_list] = NULL;
	i = 0;
	while (tmp)
	{
		str[i] = tmp->content;
		tmp = tmp->next;
		i++;
	}
	return (str);
}

void 		cmd_echo(t_list_args *list)
{
	t_list_args *tmp;
	int		flag;

	flag = 0;
	tmp = list->next;
	if (tmp && ft_strncmp(tmp->content, "-n", ft_strlen(tmp->content) + 1) == 0)
	{
		flag = 1; 
		tmp = tmp->next;
	}
	while (tmp)
	{
		write(1,tmp->content , ft_strlen(tmp->content));
		if (tmp->next)
			write(1, " ",1);
		tmp = tmp->next;
	}
	if (!flag)
		write(1, "\n",1);
}

int			find_in_env(t_env **env, char *name)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key_value[0], name, ft_strlen(tmp->key_value[0]) + 1) == 0)
		{
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int			check_name(char *var, char ch)
{
	int		i;

	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (0);
	i = -1;
	while (var[++i] != ch && var[i] != '\0')
	{
		if (!ft_isdigit(var[i]) && !ft_isalpha(var[i]) && var[i] != '_')
			return (0);
	}
	return (i);
}

void 		cmd_unset(t_env **head, char *del_str)
{
	t_env	*tmp;
	t_env 	*next_elem;

	tmp = *head;
	next_elem = *head;

	if (!check_name(del_str, '='))
		return ;
	while (next_elem && ft_strncmp(next_elem->key_value[0], del_str, ft_strlen(next_elem->key_value[0]) + 1) != 0)
		next_elem = next_elem->next;
	if (next_elem == NULL)
		return ;
	while (tmp && ft_strncmp(tmp->next->key_value[0], del_str, ft_strlen(tmp->next->key_value[0]) + 1) != 0)
		tmp = tmp->next;
	tmp->next = next_elem->next;
	free(next_elem->key_value[0]);
	free(next_elem->key_value[1]);
	free(next_elem);
	next_elem = NULL;
}

void 		start_shell(t_all *all, t_head_struct *head_struct)
{
	char	**str;

	str = get_arg(&(all->args));
	if (*str[0] == '\0') // leak
		return;
	select_cmd(head_struct, str, head_struct->all.args);
	free(str);
}

char		*get_value_env(char *var)
{
	char	*out;
	int		i;
	int		len;

	len = ft_strlen(var);
	if (!(out = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = -1;
	out[len] = '\0';
	while (var[++i] != '\0')
		out[i] = var[i];
	return (out);
}



char		*get_name_env(char *var, char ch)
{
	char	*name;
	int		i;

	if (!(i = check_name(var, ch)))
		return (NULL);
	if (!(name = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	name[i] = '\0';
	i = 0;
	while (var[i] != ch && var[i] != '\0')
	{
		name[i] = var[i];
		i++;
	}
	return (name);
}

t_env		*lst_new_env(char *name, char *value, int visable)
{
	t_env	*tmp;

	if (!(tmp = (t_env *)malloc(sizeof(t_env))))
		return (NULL);
	if (!(tmp->key_value = (char **)malloc(sizeof(char *) * 3)))
		return (NULL);
	tmp->key_value[0] = ft_strdup(name);
	if (value == NULL)
		tmp->key_value[1] = NULL;
	else
		tmp->key_value[1] = ft_strdup(value);
	tmp->key_value[2] = NULL;
	tmp->visible = visable;
	tmp->next = NULL;
	return (tmp);
}

int			init_env(char *var, t_env **env)
{
	char	*name;
	char	*value;
	t_env	*tmp;

	tmp = *env;
	if (!(name = get_name_env(var, '=')))
		return (0);
	if (!(value = get_value_env(&var[ft_strlen(name) + 1])))
		return (0);
	while (tmp && ft_strncmp(name, tmp->key_value[0], ft_strlen(name) + 1) != 0)
		tmp = tmp->next;
	if (!tmp)
	{
		add_back(env, lst_new_env(name, value, 0));
	}
	else
	{
		free(tmp->key_value[1]);
		tmp->key_value[1] = ft_strdup(value);
	}
	free(value);
	free(name);
	return (1);
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

int			redact_env(t_env **envp, char *name, char *value)
{
	t_env	*tmp;

	tmp = *envp;
	while (tmp)
	{
		if (ft_strncmp(tmp->key_value[0], name, ft_strlen(tmp->key_value[0]) + 1) == 0)
		{
			tmp->visible = 1;		//наверное нужно флаг 2 или что-то такое тк в env его не будет
			if (value != NULL)
				tmp->key_value[1] = ft_strdup(value);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void		print_export(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (tmp->visible != 0)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(tmp->key_value[0], 1);
			if (tmp->key_value[1] != NULL)
			{
				ft_putstr_fd("=", 1);
				ft_putstr_fd("\"", 1);
				ft_putstr_fd(tmp->key_value[1], 1);
				ft_putstr_fd("\"", 1);
			}
			ft_putstr_fd("\n", 1);
		}
		tmp = tmp->next;
	}
}

void		cmd_export(t_env **envp, t_list_args *args)
{
	t_list_args *tmp;
	char	*name;
	char	*value;

	if (!args->next)
	{
		print_export(envp);
	}
	else
	{
		tmp = args->next;
		while (tmp)
		{
			if (!(name = get_name_env(tmp->content, '=')))
			{
				tmp = tmp->next;
				continue;
			}
			if (find_in_env(envp, name)) // если параметр уже есть в списке env
			{
				if (ft_strchr(tmp->content, '=') != NULL) // если это пример по типу a=123sd
				{
					if (!(value = get_value_env(&(tmp->content[ft_strlen(name) + 1]))))
						return ;
					redact_env(envp, name, value);
					free(name);
					free(value);
				}
				else		// если это параметр по типу afrwg_weg без =
				{
					redact_env(envp, name, NULL);
					free (name);
				}
			}
			else			// если такого нет в списке
			{
				if (ft_strchr(tmp->content, '=') != NULL) // если это пример по типу a=123sd
				{
					if (!(value = get_value_env(&(tmp->content[ft_strlen(name) + 1]))))
						return ;
					add_back(envp, lst_new_env(name, value, 1));
					free(name);
					free(value);
				}
				else		// если это параметр по типу afrwg_weg без =
				{
					add_back(envp, lst_new_env(name, NULL, 1));
					free(name);
				}
			}
			tmp = tmp->next;
		}
	}
	return ;
}

int 		check_cond(char *str)
{
	return ((ft_strncmp(str, "cd", ft_strlen(str) + 1) == 0) ||
			(ft_strncmp(str, "pwd", ft_strlen(str) + 1) == 0) ||
			(ft_strncmp(str, "env", ft_strlen(str) + 1) == 0) ||
			(ft_strncmp(str, "unset", ft_strlen(str) + 1) == 0) ||
			(ft_strncmp(str, "echo", ft_strlen(str) + 1) == 0) ||
			(ft_strncmp(str, "exit", ft_strlen(str) + 1) == 0) ||
			(ft_strncmp(str, "export", ft_strlen(str) + 1) == 0));
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