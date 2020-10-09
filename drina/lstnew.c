
#include "minishell.h"

t_env		*lstnew(char *str, int visuble)
{
	t_env	*new_elem;

	new_elem = (t_env*)malloc(sizeof(t_env));
	if (!new_elem)
		return (NULL);
	new_elem->key_value = ft_split(str, '=');
	new_elem->visible = visuble;
	new_elem->next = NULL;
	return (new_elem);
}
