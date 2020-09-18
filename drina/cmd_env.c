
#include "minishelldrina.h"

void		cmd_env(t_env *head)
{
	t_env *tmp;

	tmp = head;
	while (tmp->next != NULL)
	{
		ft_putstr_fd( tmp->key_value[0], 1);
		ft_putstr_fd( tmp->key_value[1], 1);
		write(1, "\n" , 1);
		tmp = tmp->next;
	}
}
