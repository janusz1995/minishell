
#include "parser.h"

void	commands(t_head_struct *head_struct, char **str, t_list_args *args)
{
	if (check_cond(str[0]) == 1)
		no_system_cmd(head_struct, str, args);
	else
		system_cmd(head_struct, str);
}
