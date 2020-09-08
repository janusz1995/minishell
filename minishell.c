
#include "minishell.h"


void	add_back(t_env **head, t_env *new)
{
	t_env	*save_head;

	save_head = (*head);
	if (save_head == NULL)
		(*head) = new;
	else
	{
		while (save_head->next != NULL)
			save_head = save_head->next;
		save_head->next = new;
	}
}

t_env		*lstnew(char *str)
{
	t_env	*new_elem;

	new_elem = (t_env*)malloc(sizeof(t_env));
	if (!new_elem)
		return (NULL);
	new_elem->key_value = ft_split(str, '=');
	new_elem->next = NULL;
	return (new_elem);
}

void 	all_envp(t_env **env, char **envp)
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
	char *str1;
	char **str2;
	num = argc;
	str = argv;
	env = NULL;

	all_envp(&env, envp);
	tmp = env;

	while (21)
	{
		while (get_next_line(0, str1) == 0)
		{
			str2 = ft_split(str1,' ');
		}
		if (ft_strncmp( str2[0], "cd", 2) == 0)
		{

		}
		if (ft_strncmp( str2[0], "pwd", 3))
		{

		}





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
