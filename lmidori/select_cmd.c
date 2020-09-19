
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

char		**get_arg(t_list_args *list)
{
	char	**str;
	int 	len_list;
	int		i;

	len_list = ft_lstsize_arg(list);
	if (list)
	{
		if (!(str = (char**)malloc(sizeof(char*) * (len_list + 1))))
			return (NULL);
		str[len_list] = NULL;

		i = 0;
		while (list)
		{
			str[i] = list->content;
			list = list->next;
			i++;
		}
	}
	else
		return (NULL);
	return (str);
}

void 		select_cmd(t_all *all, t_head_struct *head_struct, char **envp)
{
	char	**str;

	str = get_arg(all->args);

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
//		else if (str[0] && (ft_strncmp(str2[0], "export", ft_strlen(str2[0])) == 0))
//		{
//
//		}
	else if (all->cmd && (ft_strncmp(all->cmd, "exit", ft_strlen(all->cmd) + 1) == 0))
		exit(0);
	else
	{
		diff_cmd(head_struct->all.cmd, head_struct->bin, envp, str);

	}
}