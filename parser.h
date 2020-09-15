/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 11:39:11 by lmidori           #+#    #+#             */
/*   Updated: 2020/09/15 23:25:10 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <unistd.h>
# include <stdio.h>
# include "libft/libft.h"
# include "libft/get_next_line.h"
# include <sys/types.h>
# include <dirent.h>

typedef struct			s_all
{
	char				*cmd;
	t_list_args			*args;
	char				*spec;
	struct s_all		*next;
}						t_all;

typedef struct			s_arg
{
	char				*arg;
	int					len;
	int					j;
}						t_arg;

typedef struct			s_env
{
	char				**key_value;
	struct s_env		*next;
}						t_env;

typedef struct			s_list_args
{
	void				*content;
	int					spec_flag;
	struct s_list_args	*next;
}						t_list_args;

t_list_args				*ft_lstnew_arg(void *content, int flag);
t_list_args				*ft_lstlast_arg(t_list_args *lst);
void					ft_lstadd_back_arg(t_list_args **lst, t_list_args *new);
void					ft_lstclear_args(t_list_args **lst, void (*del)(void*));
void					ft_lst_print(t_list_args *list);
int						parse(char *str, t_list_args **list, t_env *env);
int						len_arg(char *ptr);
int						len_marks(char *ptr, char ch, int *len);
char					*skip_spaces(char *ptr);
int						read_args(char *ptr, int len, t_list_args **list, t_env *env);
int						init_arg_marks(char *ptr, char *arg, int *j, t_env *env);
int						read_special_char(char *str, t_list_args **list);

int			parser(char *str, t_arg *arg, t_list_args **list, t_env *env);
int			read_arg(char *str, t_arg *arg, t_env *env, t_list_args **list);
int			init_arg_quotes(char *str, t_arg *arg, t_env *env);
int			init_arg_env(char *str, t_arg *arg, t_env *env);
int			str_concatenated(t_arg *arg, char *tmp1, char *tmp2);
char		*get_arg_env(char *tmp, t_env *env);
int			init_struct(t_arg *arg, int len);


#endif
