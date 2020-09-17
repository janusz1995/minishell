
#include "minishell.h"
//#include <sys/types.h>
//#include <sys/wait.h>
#include <dirent.h>
#include <signal.h>

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

char		**path_bin(t_env **head)
{
	t_env	*tmp;
	char	**str;

	tmp = (*head);
	while (tmp->next != NULL)
	{
		if ((ft_strncmp(tmp->key_value[0], "PATH=", ft_strlen(tmp->key_value[0]))) == 0)
			str = ft_split(tmp->key_value[1], ':');
		tmp = tmp->next;
	}
	return (str);
}

void 		start_programm(char *cmd, char *path_bin, char **env, char **cmd_arg)
{
	pid_t	pid;
	pid_t	wait_pid;
	char	*tmp;
	int		status;

	pid = fork();
	if (path_bin != NULL)
		tmp = ft_strjoin(path_bin, "/");
	tmp = ft_strjoin(tmp, cmd);
	if (pid == 0)
	{
		if (execve(tmp, cmd_arg, env) == -1)
		{
			ft_putstr_fd( "Error\n",2);
			exit (WEXITSTATUS(status));
		}
	}
	else if (pid < 0)
	{
		perror("lsh");
	}
	else
		wait_pid = waitpid(pid, &status, WUNTRACED);
}

void		diff_cmd(char *str, char **path_bin, char **envp, char **str2)
{
	DIR				*dir;
	struct dirent	*entry;
	int				i;
	int				flag;

	i = 0;
	flag = 0;
	while (path_bin[i])
	{
		dir = opendir(path_bin[i]);
		while ((entry = readdir(dir)) != NULL)
		{
			if ((ft_strncmp(str, entry->d_name, ft_strlen(str) + 1)) == 0)
			{
				start_programm(str, path_bin[i], envp, str2);
				flag = 1;
				break ;
			}
		}
		closedir(dir);
		i++;
		if (flag)
			break ;
	}
	if (flag == 0)
		start_programm(str, path_bin[i], envp, str2);
}

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
