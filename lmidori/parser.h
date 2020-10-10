/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 11:39:11 by lmidori           #+#    #+#             */
/*   Updated: 2020/10/10 15:42:12 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include <sys/types.h>
# include <dirent.h>
# include <sys/stat.h>
# include <signal.h>
# include <errno.h>
# include <string.h>

char					*g_str1;
pid_t					g_pid;
int						g_error;

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
	int					visible;
	struct s_env		*next;
}						t_env;

typedef struct			s_head_struct
{
	char				**bin;
	char				**new_args;
	char				**envp;
	char				*last_spec;
	t_env				*env;
	t_all				all;
	t_all				*copy_all;
	t_list_args			*list;
	int					fd[2];
	int					fd_redir;
	int					flag_pipe;
	int					flag_error;
	int					flag_redir;
	int					saveinput;
	int					saveoutput;
}						t_head_struct;

int						check_name(char *var, char ch);
int						add_new_env(t_head_struct *head_struct, char **str);
void					replace_pwd(t_env *tmp, char *oldpwd,
									char *str_cwd, int *flag);
void					find_pwd(t_env *head, t_env *tmp,
									char *oldpwd, char *str_cwd);
void					error_cd(char *str, int fd);
void					cmd_cd(char **args, t_env *head);
void					cmd_echo(t_list_args *list);
void					cmd_env(t_env *head);
void					*xmalloc(size_t len);
int						init_struct(t_arg *arg, int len);
int						fool_strcut(t_all *all, t_list_args **list);
void					ft_init_struct(t_all *all);
void					ft_clear_strcut(t_all *all);
int						redact_env(t_env **envp, char *name, char *value);
int						init_arg_quotes(char *str, t_arg *arg, t_env *env);
int						init_tilde(char *str, t_arg *arg, t_env *env);
int						init_quotes_slash(char *str, int *i,
									t_arg *arg, t_env *env);
int						read_arg(char *str, t_arg *arg,
									t_env *env, t_list_args **list);
void					sort_array(char **str, int len);
char					**creat_array(t_env **env);
void					print_varible(t_env *tmp);
void					print_export(t_env **env);
int						read_special_char(char *str, t_list_args **list);
void					init_head_struct(t_head_struct *head_struct);
int						parser(char *str, t_arg *arg,
								t_head_struct *head_struct);
void					sigquit(int sig);
void					sigint(int sig);
t_env					*new_key_value(char *str, int visible);
void					all_envp(t_env **env, char **envp);
void					add_back(t_env **head, t_env *new);
int						lstsize_env(t_env *lst, int flag);
t_env					*lst_new_env(char *name, char *value, int visable);
t_list_args				*ft_lstnew_arg(void *content, int flag);
t_list_args				*ft_lstlast_arg(t_list_args *lst);
void					ft_lstadd_back_arg(t_list_args **lst, t_list_args *new);
void					ft_lstclear_args(t_list_args **lst, void (*del)(void*));
int						ft_lstsize_arg(t_list_args *lst);
int						init_env(char *var, t_env **env);
int						str_concatenated(t_arg *arg, char *tmp1, char *tmp2);
int						init_arg_env(char *str, t_arg *arg, t_env *env);
char					*get_value_env(char *var);
char					*get_home_dir(t_env *env);
char					*get_arg_env(char *tmp, t_env *env);
char					**get_arg(t_list_args **list);
char					*skip_spaces(char *ptr);
int						len_marks(char *ptr, char ch, int *len);
int						check_len_quotes_slash(int *i, char *ptr, int *len);
int						len_arg(char *ptr);
int						find_in_env(t_env **env, char *name);
char					**init_envp(t_env *env);
void					error_unset(char *name);
void					cmd_unset(t_env **head, char *del_str);
void					cmd_pwd(void);
int						export_if_in_list(t_env **envp, char *name,
											t_list_args *tmp);
int						export_if_not_in_list(t_env **envp, char *name,
											t_list_args *tmp);
void					error_export(char *name);
void					cmd_export(t_env **envp, t_list_args *args);
long long				ft_atol_exit(const char *str);
void					error_exit(char **str);
int						check_args_exit(char **str);
void					exit_cmd(char **str);
char					*get_name_env(char *var, char ch);
void					error_directory_diff(char *dir);
void					error_command_diff(char *cmd);
void					error_fork(void);
int						find_env(t_head_struct *head_struct);
char					*init_full_path(char *path_bin, char *cmd_arg);
void					clear_double_array(char **str);
int						diff_in_path(t_head_struct *head_struct,
									char **envp, char **str2);
int						check_stat(char **cmd_arg, char *tmp);
int						skip_only_spaces(char *str);
int						exec_if_in_bin(t_head_struct *head_struct,
							char **envp, char **str2);
int						exec_fork(char **cmd_arg, char **env, char *tmp);
void					error_spec(char *spec);
int						skip_quote(char *str, char ch);
int						skip_quotes(char *str);
int						find_spec(char *str, char *spec);
int						check_right(char *str, char *spec, int *iter);
int						len_spaces(char *str);
void					error_spec(char *spec);
int						check_special(char *str, char *spec, int *i);
int						check_double_spec(char *str);
void					flows_change(t_head_struct *head_struct);


int						check_cond(char *str);
void					system_cmd(t_head_struct *head_struct, char **str2);
char					**path_bin(t_env **head);
int						start_programm_pipe(char *path_bin,
									char **env, char **cmd_arg);
int						start_programm(char *path_bin, char **env,
										char **cmd_arg);
void					start_shell(t_all *all, t_head_struct *head_struct);
void					no_system_cmd(t_head_struct *head_struct,
										char **str, t_list_args *args);
void					get_copy_all(t_all *all, t_all *copy_all,
										t_list_args *args);
int						check_and_create_void_file(t_head_struct *head_struct,
													char **str);
int						create_file(t_head_struct *head_struct, char **str);
void					start_command(t_head_struct *head_struct);
void					redirect(t_head_struct *head_struct, char **str,
								t_list_args *args);
void					cmd_pipe(t_head_struct *head_struct, char **str,
								t_list_args *args, int flag_dup);
void					select_cmd(t_head_struct *head_struct, char **str,
								t_list_args *args);
void					start_redirect(t_head_struct *head_struct, char **str,
										t_list_args *args);
void					commands(t_head_struct *head_struct,
									char **str, t_list_args *args);
void					free_list_copy(t_head_struct *head_struct);
int						error_and_free(t_head_struct *head_struct, char *str);
void					last_spec_free(t_head_struct *head_struct);
int						check_last_spec(t_head_struct *head_struct, char *str);

#endif
