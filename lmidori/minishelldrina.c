
#include "minishelldrina.h"
//#include <sys/types.h>
//#include <sys/wait.h>

void 	print_env(t_env *head)
{
	t_env	*root;

	root = head;
	while (root->next != NULL)
	{
		printf("%s%s\n", root->key_value[0], root->key_value[1]);
		root = root->next;
	}
}

int 	main(int argc, char **argv, char **envp)
{
	t_env *env, *tmp;
	int num;
	char **str;
	char *str1 = NULL;
	char **str2;
	char **bin;
	num = argc;
	str = argv;
	env = NULL;

	all_envp(&env, envp);
	add_equal(&env);

	bin = path_bin(&env);

	char *ptr;
	ptr = NULL;
	get_home_dir(&env, &ptr);

	tmp = env;
	//ft_putstr_fd(ptr, 1);

	while (21)
	{
		write(1, "shell > ", 8);
		if ((get_next_line(0, &str1)) > 0)
		{
			str2 = ft_split(str1, ' ');
			free(str1);
			str1 = NULL;
		}
		if (str2[0] && (ft_strncmp(str2[0], "cd", ft_strlen(str2[0])) == 0))
		{
			cmd_cd(str2, tmp);
		}
		else if (str2[0] && (ft_strncmp(str2[0], "pwd", ft_strlen(str2[0]))) == 0)
		{
			cmd_pwd(env);
		}
		else if (str2[0] && (ft_strncmp(str2[0] , "env", ft_strlen(str[0])) == 0))
		{
			cmd_env(env);
		}
//		else if (str[0] && (ft_strncmp(str2[0], "export", ft_strlen(str2[0])) == 0))
//		{
//
//		}
		else if (str2[0] && (ft_strncmp(str2[0], "exit", ft_strlen(str2[0]) + 1) == 0))
			exit (0);
		else
			diff_cmd(str2[0], bin, envp, str2);
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
