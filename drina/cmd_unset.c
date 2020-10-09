
#include "parser.h"

void 		cmd_unset(t_env **head, char *del_str)
{
	t_env	*tmp;
	t_env 	*next_elem;

	tmp = *head;
	next_elem = *head;

	if (!check_name(del_str, '='))
		return ;
	while (next_elem && ft_strncmp(next_elem->key_value[0], del_str, ft_strlen(next_elem->key_value[0]) + 1) != 0)
		next_elem = next_elem->next;
	if (next_elem == NULL)
		return ;
	while (tmp && ft_strncmp(tmp->next->key_value[0], del_str, ft_strlen(tmp->next->key_value[0]) + 1) != 0)
		tmp = tmp->next;
	tmp->next = next_elem->next;
	free(next_elem->key_value[0]);
	free(next_elem->key_value[1]);
	free(next_elem);
	next_elem = NULL;
}
