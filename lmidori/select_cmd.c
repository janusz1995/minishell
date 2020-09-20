
#include "parser.h"

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

char		**get_arg(t_list_args *list, char* cmd)
{
	char	**str;
	int 	len_list;
	int		i;

	i = 0;
	len_list = ft_lstsize_arg(list);

	if (!(str = (char**)malloc(sizeof(char*) * (len_list + 2))))
		return (NULL);
	str[len_list + 1] = NULL;
	str[i++] = cmd;
	while (list)
	{
		str[i] = list->content;
		list = list->next;
		i++;
	}
	return (str);
}

void 		cmd_echo(t_list_args *list)
{
	t_list_args *tmp;

	tmp = list;
	while (tmp)
	{
		write(1,tmp->content , ft_strlen(tmp->content));
		write(1, " ",1);
		tmp = tmp->next;
	}
	write(1, "\n",1);
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

void 		select_cmd(t_all *all, t_head_struct *head_struct, char **envp)
{
	char	**str;

	str = get_arg(all->args, head_struct->all.cmd);
	if (all->cmd && (ft_strncmp(all->cmd, "cd", ft_strlen(all->cmd) + 1) == 0))
	{
		cmd_cd(str, head_struct->env);
	}
	else if (all->cmd && (ft_strncmp(all->cmd, "pwd", ft_strlen(all->cmd) + 1)) == 0)
	{
		cmd_pwd(head_struct->env);
	}
	else if (all->cmd && (ft_strncmp(all->cmd, "env", ft_strlen(all->cmd) + 1) == 0))
	{
		cmd_env(head_struct->env);
	}
	else if (all->cmd && (ft_strncmp(all->cmd, "unset", ft_strlen(all->cmd) + 1) == 0))
	{
		cmd_unset(&(head_struct->env), str[1]);
	}
//		else if (str[0] && (ft_strncmp(str2[0], "export", ft_strlen(str2[0])) == 0))
//		{
//
//		}
	else if (all->cmd && (ft_strncmp(all->cmd, "echo", ft_strlen(all->cmd) + 1) == 0))
	{
		cmd_echo(head_struct->all.args);
	}
	else if (all->cmd && (ft_strncmp(all->cmd, "exit", ft_strlen(all->cmd) + 1) == 0))
		exit(0);
	else
	{
		diff_cmd(head_struct->all.cmd, head_struct->bin, envp, str);
	}
	//free (str);
}