

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include "libft/libft.h"
# include "libft/get_next_line.h"
# include <sys/types.h>
#include <dirent.h>

typedef struct 			s_env
{
	char 				**key_value;
	struct s_env		*next;
}						t_env;

typedef struct			s_list_args
{
	void				*content;
	int					spec_flag;
	struct s_list_args	*next;
}						t_list_args;


void					add_back(t_env **head, t_env *new);
t_list_args				*ft_lstnew_arg(void *content, int flag);
t_list_args				*ft_lstlast_arg(t_list_args *lst);
void					ft_lstadd_back_arg(t_list_args **lst, t_list_args *new);
void					ft_lstclear_args(t_list_args **lst, void (*del)(void*));
void					ft_lst_print(t_list_args *list);
int						parse(char *str, t_list_args **list);
int						len_arg(char *ptr);
int						len_marks(char *ptr, char ch, int *len);
char					*skip_spaces(char *ptr);
int						read_args(char *ptr, int len, t_list_args **list);
int						init_arg_marks(char *ptr, char *arg, char ch, int *j);
int						read_special_char(char *str, t_list_args **list);
void					enter_cd(t_list_args *list, t_env *env, char *home);

t_env					*lstnew(char *str);

#endif
