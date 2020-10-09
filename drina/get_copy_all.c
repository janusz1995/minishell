
#include "parser.h"

void		get_copy_all(t_all *all, t_all *copy_all, t_list_args *args)
{
	t_list_args	*tmp;
	t_all		*tmp_copy;

	tmp = args;
	tmp_copy = copy_all;
	tmp_copy->args = NULL;
	tmp_copy->spec = NULL;
	tmp_copy->equal = 0;
	tmp_copy->spec = ft_strdup(all->spec); // need defend malloc;
	while (tmp)
	{
		ft_lstadd_back_arg(&(copy_all->args),
					 ft_lstnew_arg(ft_strdup(tmp->content), tmp->spec_flag));
		tmp = tmp->next;
	}
}
