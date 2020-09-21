
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

	tmp = list->next;
	while (tmp)
	{
		write(1,tmp->content , ft_strlen(tmp->content));
		write(1, " ",1);
		tmp = tmp->next;
	}
	write(1, "\n",1);
}

void		cmd_export()
{








}

void 		cmd_unset(t_env **head, char *del_str)
{
	t_env	*tmp;
	t_env 	*next_elem;

	tmp = *head;
	next_elem = *head;

	while (next_elem && ft_strncmp(next_elem->key_value[0], del_str, ft_strlen(next_elem->key_value[0] + 1)) != 0)
		next_elem = next_elem->next;
	if (next_elem == NULL)
		return ;
	while (tmp && ft_strncmp(tmp->next->key_value[0], del_str, ft_strlen(tmp->next->key_value[0] + 1)) != 0)
		tmp = tmp->next;
	tmp->next = next_elem->next;
	free(next_elem->key_value[0]);
	free(next_elem->key_value[1]);
	free(next_elem);
}

void 		start_shell(t_all *all, t_head_struct *head_struct)
{
	char	**str;

	str = get_arg(&(all->args));
	// int i = -1;
	// while (str[++i])
	// 	printf("%s\n", str[i]);
	// if (head_struct)
	// 	i++;
	select_cmd(head_struct, str, head_struct->all.args);
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

int			check_name(char *var)
{
	int		i;

	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (0);
	i = -1;
	while (var[++i] != '=')
	{
		if (!ft_isdigit(var[i]) && !ft_isalpha(var[i]) && var[i] != '_')
			return (0);
	}
	return (i);
}

char		*get_name_env(char *var)
{
	char	*name;
	int		i;

	if (!(i = check_name(var)))
		return (NULL);
	if (!(name = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	name[i] = '\0';
	i = 0;
	while (var[i] != '=')
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
	tmp->key_value[0] = name;
	tmp->key_value[1] = value;
	tmp->key_value[2] = NULL;
	tmp->visible = visable;
	return (tmp);
}

int			init_env(char *var, t_env **env)
{
	char	*name;
	char	*value;

	if (!(name = get_name_env(var)))
		return (0);
	if (!(value = get_value_env(&var[ft_strlen(name) + 1])))
		return (0);
	
	add_back(env, lst_new_env(name, value, 0));
	return (1);
}

int			add_new_env(t_head_struct *head_struct, char **str)
{
	t_list_args *arg;
	// char		*tmp;
	int			flag;
	int			i;

	i = 0;
	flag = 1;
	arg = head_struct->all.args;
	while (arg && arg->spec_flag == 2)
	{
		if (!(flag = check_name(arg->content)))
			break;
		arg = arg->next;
		i++;
	}
	if (!flag)
	{
		select_cmd(head_struct, &str[i], arg);
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
	// if (!(init_env(arg->content, &(head_struct->env))))
	// 		return (-1);
	// arg = arg->next;
	// while (arg && arg->spec_flag == 2)
	// {
	// 	if (!(init_env(arg->content, &(head_struct->env))))
	// 		return (-1);
	// 	arg = arg->next;
	// }
	// if (!arg)
	return (1);
}

void 		select_cmd(t_head_struct *head_struct, char **str, t_list_args *args)
{
	if (head_struct->all.equal == 1)
	{
		add_new_env(head_struct, str);
	}
	else if (str[0] && (ft_strncmp(str[0], "cd", ft_strlen(str[0]) + 1) == 0))
	{
		cmd_cd(str, head_struct->env);
	}
	else if (str[0] && (ft_strncmp(str[0], "pwd", ft_strlen(str[0]) + 1)) == 0)
	{
		cmd_pwd(head_struct->env);
	}
	else if (str[0] && (ft_strncmp(str[0], "env", ft_strlen(str[0]) + 1) == 0))
	{
		cmd_env(head_struct->env);
	}
	else if (str[0] && (ft_strncmp(str[0], "unset", ft_strlen(str[0]) + 1) == 0))
	{
		cmd_unset(&(head_struct->env), str[1]);
	}
//	else if (all->cmd && (ft_strncmp(all->cmd, "export", ft_strlen(all->cmd)) == 0))
//	{
//		cmd_export();
//	}
	else if (str[0] && (ft_strncmp(str[0], "echo", ft_strlen(str[0]) + 1) == 0))
	{
		cmd_echo(args);
	}
	else if (str[0] && (ft_strncmp(str[0], "exit", ft_strlen(str[0]) + 1) == 0))
		exit(0);
	else
	{
		diff_cmd(head_struct, str);
	}
	free(str);
}