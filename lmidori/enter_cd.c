/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enter_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 22:54:58 by lmidori           #+#    #+#             */
/*   Updated: 2020/09/12 22:55:11 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		enter_cd(t_list_args *list, t_env *env, char *home)
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
