
#include "parser.h"

void		cmd_cd(char **args,t_env *env)
{
	char	*str_cwd;
	t_env	*tmp;

	tmp = env;
	if (chdir(args[0]) == -1)
	{
		ft_putstr_fd("Error\n",2);
		exit (0);
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
//	ft_putstr_fd(env->key_value[0], 1);
//	ft_putstr_fd(env->key_value[1], 1);
//	write(1, "\n" , 1);
}
