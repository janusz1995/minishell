
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

int 	main(int argc, char **argv, char **envp)
{
	t_env *env, *tmp;
	int num;
	char **str;
	char *str1 = NULL;
	char *str_cwd;
	char **str2;
	num = argc;
	str = argv;
	env = NULL;

	all_envp(&env, envp);
	tmp = env;

	write(1, "shell > ", 8);
	while (21)
	{
		if ((get_next_line(0, &str1)) > 0)
		{
			str2 = ft_split(str1, ' ');
			free(str1);
			str1 = NULL;
		}
		if (str2[0] && (ft_strncmp(str2[0], "cd", 2) == 0))
		{
			str_cwd = getcwd(NULL, 0);
			if (chdir(str2[1]) == -1)
			{
				ft_putstr_fd("Error\n",2);
				exit (0);
			}
			while (tmp->next != NULL)
			{
				if ((ft_strncmp(tmp->key_value[0], "PWD", 3)) == 0)
				{
					free(tmp->key_value[1]);
					tmp->key_value[1] = ft_strdup(str_cwd);
					break ;
				}
				tmp = tmp->next;
			}

		}
		else
			exit (0);
//		if (ft_strncmp(str2[0], "pwd", 3))
//		{
//
//		}



	}

//	while (tmp->next != NULL)
//	{
//		printf("%s = ", tmp->key_value[0]);
//		printf("%s\n", tmp->key_value[1]);
//		tmp = tmp->next;
//	}


//	pid_t copy;
//	//pid_t three;
//
//	printf("%s", "Minishell start\n");
//	copy = fork();
//	printf("Original program, pid = %d\n", getpid());
//
//	if (copy == 0)
//		printf("In child process, pid = %d, ppid = %d\n", getpid(), getppid());
//	else
//		printf("In parent, pid = %d, fork returned = %d\n", getpid(), copy);



	return (1);
}
