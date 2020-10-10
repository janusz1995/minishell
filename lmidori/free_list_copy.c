
#include "parser.h"

void 		free_list_copy(t_head_struct *head_struct)
{
	t_list_args		*tmp;

	head_struct->copy_all->equal = 0;
	free(head_struct->copy_all->spec);
	while (head_struct->copy_all->args)
	{
		tmp = head_struct->copy_all->args;
		head_struct->copy_all->args = head_struct->copy_all->args->next;
		//free(tmp->content);    // need free!!!!!
		free(tmp);
		tmp = NULL;
	}
	head_struct->copy_all->args = NULL;
	head_struct->copy_all->spec = NULL;
	free(head_struct->copy_all);
	head_struct->copy_all = NULL;
}
