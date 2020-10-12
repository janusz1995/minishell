/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diff_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 22:29:14 by lmidori           #+#    #+#             */
/*   Updated: 2020/10/12 13:53:00 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char				**init_envp(t_env *env)
{
	int				len;
	char			**array;
	int				i;
	char			*tmp1;
	char			*tmp2;

	i = -1;
	len = lstsize_env(env, 1);
	array = (char **)xmalloc(sizeof(char *) * (len + 1));
	array[len] = NULL;
	while (env != NULL)
	{
		if (env->visible == 1)
		{
			tmp1 = ft_strjoin(env->key_value[0], "=");
			tmp2 = ft_strjoin(tmp1, env->key_value[1]);
			free(tmp1);
			array[++i] = tmp2;
		}
		env = env->next;
	}
	return (array);
}

void				clear_double_array(char **str)
{
	int				i;

	i = -1;
	while (str[++i] != NULL)
		free(str[i]);
	free(str);
	str = NULL;
	return ;
}

int					exec_if_in_bin(t_head_struct *head_struct,
						char **envp, char **str2)
{
	DIR				*dir;
	int				i;
	struct dirent	*entry;

	i = 0;
	while (head_struct->bin && head_struct->bin[i])
	{
		dir = opendir(head_struct->bin[i]);
		while ((entry = readdir(dir)) != NULL)
		{
			if ((ft_strncmp(str2[0], entry->d_name,
				ft_strlen(str2[0]) + 1)) == 0)
			{
				if (head_struct->flag_pipe == 1)
					start_programm_pipe(head_struct->bin[i], envp, str2);
				else
					start_programm(head_struct->bin[i], envp, str2);
				closedir(dir);
				return (1);
			}
		}
		closedir(dir);
		i++;
	}
	return (0);
}

int					diff_in_path(t_head_struct *head_struct,
						char **envp, char **str2)
{
	int				flag;
	char			*tmp;

	if (exec_if_in_bin(head_struct, envp, str2))
		return (1);
	tmp = str2[0][0] == '.' ? "." : "";
	if (head_struct->flag_pipe == 1)
		flag = start_programm_pipe(tmp, envp, str2);
	else
		flag = start_programm(tmp, envp, str2);
	return (flag);
}

void				system_cmd(t_head_struct *head_struct, char **str2)
{
	int				flag;
	char			**envp;

	envp = init_envp(head_struct->env);
	if (head_struct->bin)
		clear_double_array(head_struct->bin);
	head_struct->bin = path_bin(&(head_struct->env));
	flag = diff_in_path(head_struct, envp, str2);
	clear_double_array(envp);
	if (flag == 0)
	{
		if (ft_strchr(str2[0], '/') != NULL)
			error_directory_diff(str2[0]);
		else
			error_command_diff(str2[0]);
	}
}
