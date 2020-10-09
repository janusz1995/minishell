
#include "parser.h"

void 		free_double_arr(char **str)
{
	int 	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

char		**init_envp(t_env *env)
{
	int		len;
	char	**array;
	int		i;
	char	*tmp1;
	char	*tmp2;

	i = -1;
	len = ft_lstlast_env(env);
	array = (char **)malloc(sizeof(char *) * (len + 1));
	array[len] = NULL;
	while (env != NULL)
	{
		if (env->visible == 1)
		{
			tmp1 = ft_strjoin(env->key_value[0], "=");
			tmp2 = ft_strjoin(tmp1, env->key_value[1]);
			free (tmp1);
			array[++i] = tmp2;
		}
		env = env->next;
	}
	return (array);
}

void				system_cmd(t_head_struct *head_struct, char **str2)
{
	DIR				*dir;
	struct dirent	*entry;
	int				i;
	int				flag;

	head_struct->envp = init_envp(head_struct->env);
	i = 0;
	flag = 0;
	while (head_struct->bin[i])
	{
		dir = opendir(head_struct->bin[i]);
		while ((entry = readdir(dir)) != NULL)
		{
			if ((ft_strncmp(str2[0], entry->d_name, ft_strlen(str2[0]) + 1)) == 0)
			{
				if (head_struct->flag_pipe == 1)
					start_programm_pipe(head_struct->bin[i], head_struct->envp, str2);
				else
					start_programm(head_struct->bin[i], head_struct->envp, str2);
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
		start_programm(head_struct->bin[i], head_struct->envp, str2);
}
