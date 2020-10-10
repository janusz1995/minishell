/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 11:39:11 by lmidori           #+#    #+#             */
/*   Updated: 2020/10/10 21:38:37 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <unistd.h>
# include <dirent.h>
# include <signal.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include "../libft/libft.h"
# include "../libft/get_next_line.h"

int						g_error;
char					*g_str1;
pid_t					g_pid;

typedef struct			s_list_args
{
	int					spec_flag;
	char				*content;
	struct s_list_args	*next;
}						t_list_args;

typedef struct			s_all
{
	int					equal;
	char				*spec;
	t_list_args			*args;
}						t_all;

typedef struct			s_arg
{
	int					j;
	int					len;
	char				*arg;
}						t_arg;

typedef struct			s_env
{
	int					visible;
	char				**key_value;
	struct s_env		*next;
}						t_env;

typedef struct			s_head_struct
{
	int					fd[2];
	int					fd_redir;
	int					flag_pipe;
	int					flag_error;
	int					flag_redir;
	int					saveinput;
	int					saveoutput;
	char				**bin;
	char				**envp;
	char				*last_spec;
	char				**new_args;
	t_all				all;
	t_all				*copy_all;
	t_env				*env;
	t_list_args			*list;
}						t_head_struct;

void					cmd_pwd(void);
void					sigint(int sig);
void					sigquit(int sig);
void					error_fork(void);
void					cmd_env(t_env *head);
void					*xmalloc(size_t len);
void					exit_cmd(char **str);
void					error_spec(char *spec);
void					error_exit(char **str);
void					error_unset(char *name);
void					error_export(char *name);
void					print_export(t_env **env);
void					print_varible(t_env *tmp);
void					ft_init_struct(t_all *all);
void					cmd_echo(t_list_args *list);
void					error_cd(char *str, int fd);
void					ft_clear_strcut(t_all *all);
void					error_command_diff(char *cmd);
void					clear_double_array(char **str);
void					error_directory_diff(char *dir);
void					sort_array(char **str, int len);
void					cmd_cd(char **args, t_env *head);
void					all_envp(t_env **env, char **envp);
void					add_back(t_env **head, t_env *new);
void					cmd_unset(t_env **head, char *del_str);
void					flows_change(t_head_struct *head_struct);
void					cmd_export(t_env **envp, t_list_args *args);
void					init_head_struct(t_head_struct *head_struct);
void					ft_lstclear_args(t_list_args **lst, void (*del)(void*));
void					ft_lstadd_back_arg(t_list_args **lst, t_list_args *new);
void					find_pwd(t_env *head, t_env *tmp,
										char *oldpwd, char *str_cwd);
void					replace_pwd(t_env *tmp, char *oldpwd,
									char *str_cwd, int *flag);
int						len_arg(char *ptr);
int						len_spaces(char *str);
int						skip_quotes(char *str);
int						skip_only_spaces(char *str);
int						check_args_exit(char **str);
int						check_double_spec(char *str);
int						check_name(char *var, char ch);
int						skip_quote(char *str, char ch);
int						find_spec(char *str, char *spec);
int						init_struct(t_arg *arg, int len);
int						lstsize_env(t_env *lst, int flag);
int						ft_lstsize_arg(t_list_args *lst);
int						init_env(char *var, t_env **env);
int						find_env(t_head_struct *head_struct);
int						find_in_env(t_env **env, char *name);
int						check_stat(char **cmd_arg, char *tmp);
int						len_marks(char *ptr, char ch, int *len);
int						fool_strcut(t_all *all, t_list_args **list);
int						check_special(char *str, char *spec, int *i);
int						check_right(char *str, char *spec, int *iter);
int						init_tilde(char *str, t_arg *arg, t_env *env);
int						init_arg_env(char *str, t_arg *arg, t_env *env);
int						read_special_char(char *str, t_list_args **list);
int						exec_fork(char **cmd_arg, char **env, char *tmp);
int						redact_env(t_env **envp, char *name, char *value);
int						init_arg_quotes(char *str, t_arg *arg, t_env *env);
int						add_new_env(t_head_struct *head_struct, char **str);
int						check_len_quotes_slash(int *i, char *ptr, int *len);
int						str_concatenated(t_arg *arg, char *tmp1, char *tmp2);
int						parser(char *str, t_arg *arg,
										t_head_struct *head_struct);
int						parse_and_do(char **str, t_arg *arg,
										t_head_struct *head_struct);
int						parser(char *str, t_arg *arg,
											t_head_struct *head_struct);
int						export_if_in_list(t_env **envp, char *name,
											t_list_args *tmp);
int						export_if_not_in_list(t_env **envp, char *name,
											t_list_args *tmp);
int						diff_in_path(t_head_struct *head_struct,
											char **envp, char **str2);
int						exec_if_in_bin(t_head_struct *head_struct,
											char **envp, char **str2);
int						init_quotes_slash(char *str, int *i,
											t_arg *arg, t_env *env);
int						read_arg(char *str, t_arg *arg,
											t_env *env, t_list_args **list);
int						len_numb(int c);
char					*skip_spaces(char *ptr);
char					**init_envp(t_env *env);
char					*get_value_env(char *var);
char					*get_home_dir(t_env *env);
char					**creat_array(t_env **env);
char					**get_arg(t_list_args **list);
char					*get_name_env(char *var, char ch);
char					*get_arg_env(char *tmp, t_env *env);
char					*init_full_path(char *path_bin, char *cmd_arg);
long long				ft_atol_exit(const char *str);
t_env					*new_key_value(char *str, int visible);
t_env					*lst_new_env(char *name, char *value, int visable);
t_list_args				*ft_lstlast_arg(t_list_args *lst);
t_list_args				*ft_lstnew_arg(void *content, int flag);
t_list_args				*free_and_go_next(t_list_args *list);

void					start_command(t_head_struct *head_struct);
void					free_list_copy(t_head_struct *head_struct);
void					last_spec_free(t_head_struct *head_struct);
void					start_shell(t_all *all, t_head_struct *head_struct);
void					system_cmd(t_head_struct *head_struct, char **str2);
void					start_redirect(t_head_struct *head_struct, char **str,
											t_list_args *args);
void					commands(t_head_struct *head_struct,
											char **str, t_list_args *args);
void					no_system_cmd(t_head_struct *head_struct,
											char **str, t_list_args *args);
void					get_copy_all(t_all *all, t_all *copy_all,
											t_list_args *args);
void					redirect(t_head_struct *head_struct, char **str,
											t_list_args *args);
void					cmd_pipe(t_head_struct *head_struct, char **str,
											t_list_args *args, int flag_dup);
void					select_cmd(t_head_struct *head_struct, char **str,
											t_list_args *args);
int						check_cond(char *str);
int						create_file(t_head_struct *head_struct, char **str);
int						error_and_free(t_head_struct *head_struct, char *str);
int						check_last_spec(t_head_struct *head_struct, char *str);
int						start_programm(char *path_bin, char **env,
											char **cmd_arg);
int						check_and_create_void_file(t_head_struct *head_struct,
											char **str);
int						start_programm_pipe(char *path_bin,
											char **env, char **cmd_arg);
char					**path_bin(t_env **head);

#endif
