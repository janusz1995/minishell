/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 22:27:57 by lmidori           #+#    #+#             */
/*   Updated: 2020/10/10 16:29:55 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	sigquit(int sig)
{
	g_str1[ft_strlen(g_str1) - 1] = '\0';
	write(1, "\nshell > ", 8);
	return ;
}

void	sigint(int sig)
{
	if (g_str1 && ft_strlen(g_str1))
	{
		free(g_str1);
		g_str1 = (char *)malloc(sizeof(char));
		g_str1[0] = '\0';
	}
	write(1, "\nshell > ", 8);
}

void	init(t_head_struct *head_struct, char **envp)
{
	signal(SIGINT, sigint);
	signal (SIGINT, SIG_DFL);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, sigquit);

	head_struct->env = NULL;
	head_struct->list = NULL;
	head_struct->new_args = NULL;
	head_struct->copy_all = NULL;
	head_struct->envp = NULL;
	head_struct->last_spec = NULL;
	head_struct->flag_error = 0;

	all_envp(&(head_struct->env), envp);
	head_struct->bin = path_bin(&(head_struct->env));

	head_struct->saveinput = dup(0);
	head_struct->saveoutput = dup(1);
	head_struct->flag_redir = 0;
	g_error = 0;
}

int		main(int argc, char **argv, char **envp)
{
	char			*str1;
	char			**arr;
	int				num;
	int				res;
	t_arg			arg;
	t_head_struct	head_struct;

	arr = argv;
	num = argc;

	str1 = NULL;
	init(&head_struct, envp);
	while (21)
	{
		head_struct.flag_pipe = 0;
		dup2(head_struct.saveinput, 0);
		dup2(head_struct.saveoutput, 1);
		write(1, "shell > ", 8);
		if ((res = get_next_line(0, &g_str1)) > 0)
		{
			if (parser(g_str1, &arg, &head_struct) != -1)
			{
				free(g_str1);
				g_str1 = NULL;
			}
			else
			{
				if (g_str1)
					free(g_str1);
				g_str1 = NULL;
			}
		}
		if (res == 0)
		{
			ft_putstr_fd("\n", 1);
			exit (0);
		}
		ft_lstclear_args(&head_struct.list, free);
		head_struct.list = NULL;
<<<<<<< HEAD

=======
>>>>>>> bda289e7d0a7afff83d3395abc81fa8742ab18f9
	}
	dup2(head_struct.saveinput, 0);
	dup2(head_struct.saveoutput, 1);
	close(head_struct.saveinput);
	close(head_struct.saveoutput);
	return (1);
}