#include "minishell.h"

void		all_envp(t_env **env, char **envp)
{
	int i;

	i = 0;
	while (envp[i] != NULL)
	{
		add_back(env, lstnew(envp[i]));
		i++;
	}

}

void		get_home_dir(t_env *env, char **str)
{
	while (env->next != NULL)
	{
		if ((ft_strncmp(env->key_value[0], "HOME", 4)) == 0)
		{
			*str = env->key_value[1];
		}
		env = env->next;
	}
}


int 	main(int argc, char **argv, char **envp)
{
	t_env *env;
	char *str1;
	t_list_args *list;
	char **arr;
	int num;
	char *home;

	arr = argv;
	num = argc;

	str1 = NULL;
	env = NULL;
	list = NULL;
	home = NULL;

	all_envp(&env, envp);
	// get_home_dir(tmp, &home);
	// ft_putstr_fd(home, 1);
	// write(1, "\n" , 1);

	while (21)
	{
		write(1, "shell > ", 8);
		if ((get_next_line(0, &str1)) > 0)
		{
			if (parse(str1, &list) != -1)
			{
				ft_lst_print(list);
				free(str1);
				str1 = NULL;
			}
			else
				ft_putstr_fd("ERROR\n", 2);
		}
		ft_lstclear_args(&list, free);
		list = NULL;
	}
	return (1);
}
