
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

void		enter_cda(t_list *list, t_env *env, char *home)
{
	char	*str_cwd;
	char	*path;
	char	*tmp;

	if (!list)
		path = home;
	else
		path = list->content;
	if (*path == '~')			// this is real shit, but i don't want write this func without Drina
	{
		tmp = path;
		path = ft_strtrim(path, "~");
		free(tmp);
		tmp = path;
		path = ft_strjoin(home, path);
		free(tmp);
	}
	if (chdir(path) == -1)
	{
		perror("Error:");
		return ;
	}
	str_cwd = getcwd(NULL, 0);
	while (env->next != NULL)
	{
		if ((ft_strncmp(env->key_value[0], "PWD", 3)) == 0)
		{
			free(env->key_value[1]);
			env->key_value[1] = ft_strdup(str_cwd);
			break;
		}
		env = env->next;
	}
	ft_putstr_fd(env->key_value[0], 1);
	write(1, "=" , 1);
	ft_putstr_fd(env->key_value[1], 1);
	write(1, "\n" , 1);
}

void		enter_cd(char **str, t_env *env)
{
	char *str_cwd;

	if (chdir(str[1]) == -1)
	{
		perror("Error");
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
	write(1, "=" , 1);
	ft_putstr_fd(env->key_value[1], 1);
	write(1, "\n" , 1);
}

char		*skip_spaces(char *ptr)
{
	while (*ptr == ' ')
		ptr++;
	return (ptr);
}

char		*read_str(char *ptr)		// we can use strdup!
{
	int		i;
	int		len;
	char	*out;

	i = 0;
	if (!ptr || *ptr == '\0')
		return (NULL);
	while (ptr[i] != ' ' && ptr[i] != '\0')
		i++;
	len = i;
	if (!(out = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	out[len] = '\0';
	i = 0;
	while (i < len)
	{
		out[i] = ptr[i];
		i++;
	}
	return (out);
}

char		*read_str_kov(char *ptr)		// this func is modificated read_str func, we need merge this 2 funcs with 1
{
	int		i;
	int		len;
	char	*out;

	i = 0;
	if (!ptr || *ptr == '\0')
		return (NULL);
	while (ptr[i] != '\"' && ptr[i] != '\0')
		i++;
	if (ptr[i] != '\"')
		return (NULL);
	len = i;
	if (!(out = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	out[len] = '\0';
	i = 0;
	while (i < len)
	{
		out[i] = ptr[i];
		i++;
	}
	return (out);
}

t_list		**parse_str(char *str1, t_list **list)
{
	char	*tmp;
	char	*str;

	tmp = NULL;
	str = ft_strtrim(str1, "\t ");
	while (*str != '\0')
	{
		str = skip_spaces(str);
		if (*str == '\"')
		{
			str++;
			if ((tmp = read_str_kov(str)) == NULL)
				return (NULL);
			ft_lstadd_back(list, ft_lstnew(tmp));
			str += ft_strlen(tmp) + 1;
			continue;
		}
		if ((tmp = read_str(str)) == NULL)
			return (NULL);
		ft_lstadd_back(list, ft_lstnew(tmp));
		str += ft_strlen(tmp);
	}
	return (list);

}

void	ft_lst_print(t_list *list)
{
	ft_putstr_fd("		START LIST\n", 2);
	while (list)
	{
		ft_putstr_fd((char *)list->content, 1);
		write(1, "\n", 1);
		list = list->next;
	}
	ft_putstr_fd("		END LIST\n", 2);
}

int 	main(int argc, char **argv, char **envp)
{
	t_env *env, *tmp;
	char *str1;
	char **str2;
	t_list *list;
	char **kek;
	int kek2;
	kek = argv;
	kek2 = argc;

	str1 = NULL;
	env = NULL;
	list = NULL;

	all_envp(&env, envp);
	tmp = env;
	char *home;
	home = NULL;
	get_home_dir(tmp, &home);
	ft_putstr_fd(home, 1);
	write(1, "\n" , 1);

	while (21)
	{
		write(1, "shell > ", 8);
		if ((get_next_line(0, &str1)) > 0)
		{
			if (*skip_spaces(str1) == '\0' || parse_str(str1, &list) == NULL)	// check malloc errors and empty line
			{
				ft_lstclear(&list, free);
				free(str1);
				str1 = NULL;
				continue;
			}
			//ft_lst_print(list);
			str2 = ft_split(str1, ' ');
			free(str1);
			str1 = NULL;
		}

		if (ft_strncmp(list->content, "cd", ft_strlen(list->content)) == 0)
		{
			enter_cda(list->next, env, home);
			ft_lstclear(&list, free);
			list = NULL;
			continue;
		}
		ft_lstclear(&list, free);
		list = NULL;
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
