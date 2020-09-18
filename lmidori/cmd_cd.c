
#include "parser.h"

void		cmd_cd(char **str, t_env *env)
{
	char *str_cwd;

	if (chdir(str[1]) == -1)
	{
		ft_putstr_fd("Error\n",2);
		exit (0);
	}
	str_cwd = getcwd(NULL, 0);
	while (env->next != NULL)
	{
		if ((ft_strncmp(env->key_value[0], "PWD=", ft_strlen(env->key_value[0]))) == 0)
		{
			free(env->key_value[1]);
			env->key_value[1] = ft_strdup(str_cwd);
			break ;
		}
		env = env->next;
	}
//	ft_putstr_fd(env->key_value[0], 1);
//	ft_putstr_fd(env->key_value[1], 1);
//	write(1, "\n" , 1);
}
