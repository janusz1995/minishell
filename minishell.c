
#include "minishell.h"


void 	print_env(t_env *root)
{
	while (root->next != NULL)
	{
		printf("%s%s\n", root->key_value[0], root->key_value[1]);
		root = root->next;
	}
}


void		cmd_env(t_env *head)
{
	t_env *tmp;

	tmp = head;
	while (tmp->next != NULL)
	{
		ft_putstr_fd( tmp->key_value[0], 1);
		ft_putstr_fd( tmp->key_value[1], 1);
		write(1, "\n" , 1);
		tmp = tmp->next;
	}
}

void		enter_cd(char **str, t_env *env)
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
		if ((ft_strncmp(env->key_value[0], "PWD", 3)) == 0)
		{
			free(env->key_value[1]);
			env->key_value[1] = ft_strdup(str_cwd);
			break ;
		}
		env = env->next;
	}
	ft_putstr_fd(env->key_value[0], 1);
	ft_putstr_fd(env->key_value[1], 1);
	write(1, "\n" , 1);
}

int 	main(int argc, char **argv, char **envp)
{
	t_env *env, *tmp;
	int num;
	char **str;
	char *str1 = NULL;
	char **str2;
	num = argc;
	str = argv;
	env = NULL;

	all_envp(&env, envp);
	add_equal(&env);

	char *ptr;
	ptr = NULL;
	get_home_dir(&env, &ptr);

	tmp = env;
	print_env(tmp);
	sort_list(env);
	tmp = env;
	print_env(tmp);
	ft_putstr_fd(ptr, 1);
	write(1, "\n" , 1);

	while (21)
	{
		write(1, "shell > ", 8);
		if ((get_next_line(0, &str1)) > 0)
		{
			str2 = ft_split(str1, ' ');
			free(str1);
			str1 = NULL;
		}
		// opendir()
		if (str2[0] && (ft_strncmp(str2[0], "cd", ft_strlen(str2[0])) == 0))
		{
			enter_cd(str2, tmp);
		}
		else
			exit (0);

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
