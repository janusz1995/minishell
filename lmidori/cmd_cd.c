/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 23:14:13 by lmidori           #+#    #+#             */
/*   Updated: 2020/10/10 22:16:25 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void		replace_pwd(t_env *tmp, char *oldpwd, char *str_cwd, int *flag)
{
	if ((ft_strncmp(tmp->key_value[0], "OLDPWD",
		ft_strlen(tmp->key_value[0]) + 1)) == 0)
	{
		*flag = 1;
		tmp->visible = 1;
		free(tmp->key_value[1]);
		tmp->key_value[1] = ft_strdup(oldpwd);
	}
	if ((ft_strncmp(tmp->key_value[0], "PWD",
		ft_strlen(tmp->key_value[0]) + 1)) == 0)
	{
		free(tmp->key_value[1]);
		tmp->key_value[1] = ft_strdup(str_cwd);
	}
	return ;
}

void		find_pwd(t_env *head, t_env *tmp, char *oldpwd, char *str_cwd)
{
	int		flag;
	char	*pwd;

	flag = 0;
	while (tmp->next != NULL)
	{
		replace_pwd(tmp, oldpwd, str_cwd, &flag);
		tmp = tmp->next;
	}
	if (!flag)
	{
		pwd = ft_strdup("OLDPWD=");
		add_back(&head, new_key_value(pwd, 1));
		free(pwd);
	}
}

void		error_cd(char *str, int fd)
{
	ft_putstr_fd("minishell: cd: no such file or directory: ", fd);
	ft_putstr_fd(str, fd);
	ft_putstr_fd("\n", fd);
	g_error = 1;
}

void		cmd_cd(char **args, t_env *head)
{
	char	*str_cwd;
	t_env	*tmp;
	char	*dir;
	char	*oldpwd;

	tmp = head;
	g_error = 0;
	if (args[1] == NULL)
		dir = get_home_dir(head);
	else
		dir = args[1];
	oldpwd = getcwd(NULL, 0);
	if (chdir(dir) == -1)
	{
		free(oldpwd);
		error_cd(dir, 2);
		return ;
	}
	if (!args[1])
		free(dir);
	str_cwd = getcwd(NULL, 0);
	find_pwd(head, tmp, oldpwd, str_cwd);
	free(oldpwd);
	free(str_cwd);
}
