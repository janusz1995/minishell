#include "minishell.h"
#include "../Drina/minishelldrina.h"

t_env		*new_key_value(char *str, int visible)
{
	t_env	*new_elem;
	int		count;

	new_elem = (t_env*)malloc(sizeof(t_env));
	if (!new_elem)
		return (NULL);
	count = 0;
	while (str[count] != '\0' && str[count] != '=')
		count++;
	str[count] = '\0';
	if (!(new_elem->key_value = (char **)malloc(sizeof(char *) * 3)))
		return (NULL);
	new_elem->key_value[0] = ft_strdup(str);
	if (str[count + 1] == '\0')
		new_elem->key_value[1] = ft_strdup("");
	else
		new_elem->key_value[1] = ft_strdup(&str[count + 1]);
	new_elem->key_value[2] = NULL;
	new_elem->visible = visible;
	new_elem->next = NULL;
	return (new_elem);
}

void		all_envp(t_env **env, char **envp)
{
	int i;
	int	flag;

	i = 0;
	flag = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp("OLDPWD", envp[i], 6) == 0)
			flag = 1;
		add_back(env, new_key_value(envp[i], 1));
		i++;
	}
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

	int 	saveinput;
	int 	saveoutput;

	saveinput = dup(0);
	saveoutput = dup(1);
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
	close(saveinput);
	close(saveoutput);
	return (1);
}