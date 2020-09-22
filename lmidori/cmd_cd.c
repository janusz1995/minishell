
#include "parser.h"

void		cmd_cd(char **args, t_env *head)
{
	char	*str_cwd;
	t_env	*tmp;
	char	*dir;

	tmp = head;
	if (args[1] == NULL)
		dir = get_home_dir(head);
	else
		dir = args[1];
	if (chdir(dir) == -1)
	{
		ft_putstr_fd("Error\n",2);
		return ;
	}
	str_cwd = getcwd(NULL, 0);
	while (tmp->next != NULL)
	{
		if ((ft_strncmp(tmp->key_value[0], "PWD=", ft_strlen(tmp->key_value[0]))) == 0)
		{
			free(tmp->key_value[1]);
			tmp->key_value[1] = ft_strdup(str_cwd);
			break ;
		}
		tmp = tmp->next;
	}
}
