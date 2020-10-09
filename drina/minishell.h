/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 16:37:25 by lmidori           #+#    #+#             */
/*   Updated: 2020/10/01 16:40:31 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include <sys/types.h>
# include <dirent.h>
# include "parser.h"
#include <signal.h>



void					add_back(t_env **head, t_env *new);
t_env					*lstnew(char *str, int visuble);
void					enter_cd(t_list_args *list, t_env *env, char *home);
char					*get_home_dir(t_env *env);

#endif
