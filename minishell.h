

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include "libft/libft.h"
# include "libft/get_next_line.h"


typedef struct 			s_env
{
	char 				**key_value;
	struct s_env		*next;
}						t_env;


#endif
