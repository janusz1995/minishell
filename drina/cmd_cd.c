
#include "parser.h"
#include "minishell.h"

void		cmd_cd(char **args, t_env *head)
{
	char	*str_cwd;
	t_env	*tmp;
	char	*dir;
	char	*oldpwd;
	int		flag;

	flag = 0;
	tmp = head;
	if (args[1] == NULL)
		dir = get_home_dir(head);
	else
		dir = args[1];
	oldpwd = getcwd(NULL, 0);
	if (chdir(dir) == -1)
	{
		ft_putstr_fd("Error\n",2);
		return ;
	}
	if (!args[1])
		free(dir);
	str_cwd = getcwd(NULL, 0);
	while (tmp->next != NULL)
	{
		if ((ft_strncmp(tmp->key_value[0], "OLDPWD", ft_strlen(tmp->key_value[0]) + 1)) == 0)
		{
			flag = 1;
			tmp->visible = 1;
			free(tmp->key_value[1]);
			tmp->key_value[1] = ft_strdup(oldpwd);
		}
		if ((ft_strncmp(tmp->key_value[0], "PWD", ft_strlen(tmp->key_value[0]) + 1)) == 0)
		{
			free(tmp->key_value[1]);
			tmp->key_value[1] = ft_strdup(str_cwd);
		}
		tmp = tmp->next;
	}
	if (!flag)
	{
		char *pwd = ft_strdup("OLDPWD=");
		add_back(&head, new_key_value(pwd, 1));
		free(pwd);
	}
	free(oldpwd);
	free(str_cwd);
}
