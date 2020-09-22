/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 11:39:11 by lmidori           #+#    #+#             */
/*   Updated: 2020/09/22 17:48:50 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <unistd.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include <sys/types.h>
# include <dirent.h>

typedef struct			s_list_args
{
	char				*content;
	int					spec_flag;
	struct s_list_args	*next;
}						t_list_args;

typedef struct			s_all
{
	int					equal;
	t_list_args			*args;
	char				*spec;
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
	int 				visible;
	struct s_env		*next;
}						t_env;

typedef struct			s_head_struct
{
	char				**bin;
	t_env				*env;
	t_all				all;
	t_list_args			*list;
}						t_head_struct;

void					ft_lstadd_back_arg(t_list_args **lst, t_list_args *new);
void					ft_lstclear_args(t_list_args **lst, void (*del)(void*));
void					ft_lst_print(t_list_args *list);

void 					start_programm(char *cmd, char *path_bin, char **env, char **cmd_arg);
void					diff_cmd(t_head_struct *head_struct, char **str2);
void					cmd_cd(char **args, t_env *head);
void					cmd_env(t_env *head);
void 					cmd_pwd();
void 					select_cmd(t_head_struct *head_struct, char **str, t_list_args *args);
void 					start_shell(t_all *all, t_head_struct *head_struct);

void					ft_init_struct(t_all *all);
void					ft_clear_strcut(t_all *all);

int						ft_lstlast_env(t_env *lst);
int						parse(char *str, t_list_args **list, t_env *env);
int						len_arg(char *ptr);
int						len_marks(char *ptr, char ch, int *len);
int						read_args(char *ptr, int len, t_list_args **list, t_env *env);
int						init_arg_marks(char *ptr, char *arg, int *j, t_env *env);
int						read_special_char(char *str, t_list_args **list);
int						parser(char *str, t_arg *arg, t_head_struct	*head_struct);
int						read_arg(char *str, t_arg *arg, t_env *env, t_list_args **list);
int						init_arg_quotes(char *str, t_arg *arg, t_env *env);
int						init_arg_env(char *str, t_arg *arg, t_env *env);
int						str_concatenated(t_arg *arg, char *tmp1, char *tmp2);
int						init_struct(t_arg *arg, int len);
int						init_tilde(char *str, t_arg *arg, t_env *env);
int						init_quotes_slash(char *str, int *i, t_arg *arg, t_env *env);
int						init_arg_env(char *str, t_arg *arg, t_env *env);
int						str_concatenated(t_arg *arg, char *tmp1, char *tmp2);
int						init_struct(t_arg *arg, int len);
int						fool_strcut(t_all *all, t_list_args **list);

char					*get_home_dir(t_env *env);
char					*get_arg_env(char *tmp, t_env *env);
char					*get_arg_env(char *tmp, t_env *env);
char					*skip_spaces(char *ptr);

char					**path_bin(t_env **head);

t_list_args				*ft_lstnew_arg(void *content, int flag);
t_list_args				*ft_lstlast_arg(t_list_args *lst);

t_env					*new_key_value(char *str, int visible);


#endif
