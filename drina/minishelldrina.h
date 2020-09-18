

#ifndef MINISHELLDRINA_H
# define MINISHELLDRINA_H

# include <unistd.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include "../lmidori/parser.h"

//typedef struct 			s_env
//{
//	char 				**key_value;
//	struct s_env		*next;
//}						t_env;


//void					add_back(t_env **head, t_env *new);
//void					all_envp(t_env **env, char **envp);
void 					add_equal(t_env **head);
//void					get_home_dir(t_env **head, char **str);
void					sort_list(t_env **head);
void 					cmd_pwd(t_env *head);
void					cmd_env(t_env *head);

//t_env					*lstnew(char *str);

#endif
