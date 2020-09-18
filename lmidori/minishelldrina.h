

#ifndef MINISHELLDRINA_H
# define MINISHELLDRINA_H

# include <unistd.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include <dirent.h>
# include <signal.h>
# include "parser.h"


void					add_back(t_env **head, t_env *new);
void					all_envp(t_env **env, char **envp);
void 					add_equal(t_env **head);
void					get_home_dir(t_env **head, char **str);
void					sort_list(t_env **head);
void 					cmd_pwd(t_env *head);
void					cmd_env(t_env *head);
void					cmd_cd(char **str, t_env *env);
void					diff_cmd(char *str, char **path_bin, char **envp, char **str2);
void 					start_programm(char *cmd, char *path_bin, char **env, char **cmd_arg);

char					**path_bin(t_env **head);

t_env					*lstnew(char *str);

#endif
