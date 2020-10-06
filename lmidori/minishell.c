/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 22:27:57 by lmidori           #+#    #+#             */
/*   Updated: 2020/10/06 18:58:46 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	sigquit(int sig)
{
	sig = 9;
	g_str1[ft_strlen(g_str1) - 1] = '\0';
	return ;
}

void	sigint(int sig)
{
	sig = 9;
	if (g_pid != 0)
		kill(g_pid, sig);
	if (g_str1 && ft_strlen(g_str1))
	{
		free(g_str1);
		g_str1 = (char *)malloc(sizeof(char));
		g_str1[0] = '\0';
	}
	write(1, "\nshell > ", 9);
}


int		main(int argc, char **argv, char **envp)
{
	char *str1;
	char **arr;
	int num;
	t_arg arg;
	
	arr = argv;
	num = argc;


	signal(SIGINT, sigint);
	signal(SIGQUIT, sigquit);

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
	head_struct.p_copy = NULL;
	head_struct.flag_redir = 0;
	int res;
	g_error = 0;
	while (21)
	{
		head_struct.flag_pipe = 0;
		dup2(saveinput, 0);
		dup2(saveoutput, 1);
		write(1, "shell > ", 8);
		if ((res = get_next_line(0, &g_str1)) > 0)
		{
			if (parser(g_str1, &arg, &head_struct) != -1)
			{
				// ft_lst_print(list);
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
		//ft_push_args(&all, &list);
		ft_lstclear_args(&head_struct.list, free);
		head_struct.list = NULL;
//		dup2(saveinput, 0);
//		dup2(saveoutput, 1);
	}
	close(saveinput);
	close(saveoutput);
	return (1);
}