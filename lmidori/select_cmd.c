/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 22:29:05 by lmidori           #+#    #+#             */
/*   Updated: 2020/10/10 22:41:01 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	start_shell(t_all *all, t_head_struct *head_struct)
{
	int		i;
	char	**str;

	i = -1;
	str = get_arg(&(all->args));
	if (*str[0] == '\0' && all->spec == NULL)
	{
		free(str);
		return ;
	}
	if (head_struct->flag_error == 0)
		select_cmd(head_struct, str, head_struct->all.args);
	free(str);
}

void	no_system_cmd(t_head_struct *head_struct, char **str, t_list_args *args)
{
	int i;

	i = 0;
	if (str[0] && (ft_strncmp(str[0], "cd", ft_strlen(str[0]) + 1) == 0))
		cmd_cd(str, head_struct->env);
	else if (str[0] && (ft_strncmp(str[0], "pwd", ft_strlen(str[0]) + 1)) == 0)
		cmd_pwd();
	else if (str[0] && (ft_strncmp(str[0], "env", ft_strlen(str[0]) + 1) == 0))
		cmd_env(head_struct->env);
	else if (str[0] && (ft_strncmp(str[0], "unset",
											ft_strlen(str[0]) + 1) == 0))
	{
		while (str[++i])
			cmd_unset(&(head_struct->env), str[i]);
	}
	else if (str[0] && (ft_strncmp(str[0], "export",
											ft_strlen(str[0]) + 1) == 0))
		cmd_export(&(head_struct->env), args);
	else if (str[0] && (ft_strncmp(str[0], "echo", ft_strlen(str[0]) + 1) == 0))
		cmd_echo(args);
	else if (str[0] && (ft_strncmp(str[0], "exit", ft_strlen(str[0]) + 1) == 0))
		exit_cmd(str);
}

void	get_copy_all(t_all *all, t_all *copy_all, t_list_args *args)
{
	t_list_args		*tmp;
	t_all			*tmp_copy;

	tmp = args;
	tmp_copy = copy_all;
	tmp_copy->args = NULL;
	tmp_copy->spec = NULL;
	tmp_copy->equal = 0;
	tmp_copy->spec = ft_strdup(all->spec);
	while (tmp)
	{
		ft_lstadd_back_arg(&(copy_all->args),
					ft_lstnew_arg(ft_strdup(tmp->content), tmp->spec_flag));
		tmp = tmp->next;
	}
}

void	start_redirect(t_head_struct *head_struct, char **str,
															t_list_args *args)
{
	t_list_args		*tmp;

	if (head_struct->copy_all != NULL)
	{
		tmp = args;
		while (tmp && tmp->next != NULL)
		{
			ft_lstadd_back_arg(&(head_struct->copy_all->args),
			ft_lstnew_arg(ft_strdup(tmp->next->content), tmp->next->spec_flag));
			tmp = tmp->next;
		}
	}
	redirect(head_struct, str, args);
}

void	select_cmd(t_head_struct *head_struct, char **str,
														t_list_args *args)
{
	int		flag;

	flag = 0;
	head_struct->flag_pipe = 0;
	if ((flag = head_struct->all.equal) == 1)
		add_new_env(head_struct, str);
	if (head_struct->flag_redir || (head_struct->all.spec
								&& (*(head_struct->all.spec) == '>'
					|| (ft_strncmp(head_struct->all.spec, ">>", 3) == 0)
					|| *(head_struct->all.spec) == '<')))
		start_redirect(head_struct, str, args);
	else if (head_struct->all.spec && *(head_struct->all.spec) == '|')
	{
		if (args != NULL)
		{
			head_struct->flag_pipe = 1;
			cmd_pipe(head_struct, str, args, 0);
		}
	}
	else
	{
		if (!flag)
			commands(head_struct, str, args);
	}
}
