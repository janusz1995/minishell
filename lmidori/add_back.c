
#include "minishell.h"

void	add_back(t_env **head, t_env *new)
{
	t_env	*save_head;

	save_head = (*head);
	if (save_head == NULL)
		(*head) = new;
	else
	{
		while (save_head->next != NULL)
			save_head = save_head->next;
		save_head->next = new;
	}

}
