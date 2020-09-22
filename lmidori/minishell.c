#include "minishell.h"
#include "../drina/minishelldrina.h"

void		all_envp(t_env **env, char **envp)
{
	int i;
	int	flag;

	flag = 0;
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp("OLDPWD", envp[i], 7) == 0)
			flag = 1;
		add_back(env, lstnew(envp[i], 1));
		i++;
	}
	if (!flag)
		add_back(env, lstnew("OLDPWD=", 2));
}



int		main(int argc, char **argv, char **envp)
{
	char *str1;
	char **arr;
	int num;
	t_arg arg;
	
	arr = argv;
	num = argc;


	t_head_struct	head_struct;
	str1 = NULL;
	head_struct.env = NULL;
	head_struct.list = NULL;
	// head_struct.list->next = NULL;
	// head_struct.list->content = NULL;

	//home = NULL;

	// t_all all;

	// all = NULL;

	all_envp(&(head_struct.env), envp);
	head_struct.bin = path_bin(&(head_struct.env));
//	add_equal(&head_struct.env);

	// get_home_dir(tmp, &home);
	// ft_putstr_fd(home, 1);
	// write(1, "\n" , 1);

	while (21)
	{
		write(1, "shell > ", 8);
		if ((get_next_line(0, &str1)) > 0)
		{
			if (parser(str1, &arg, &head_struct) != -1)
			{
				// ft_lst_print(list);
				free(str1);
				str1 = NULL;
			}
			else
				ft_putstr_fd("ERROR\n", 2);
		}
		//ft_push_args(&all, &list);
		ft_lstclear_args(&head_struct.list, free);
		head_struct.list = NULL;
	}
	return (1);
}