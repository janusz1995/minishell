
#include "parser.h"

t_env		*lst_new_env(char *name, char *value, int visable)
{
	t_env	*tmp;

	if (!(tmp = (t_env *)malloc(sizeof(t_env))))
		return (NULL);
	if (!(tmp->key_value = (char **)malloc(sizeof(char *) * 3)))
		return (NULL);
	tmp->key_value[0] = ft_strdup(name);
	if (value == NULL)
		tmp->key_value[1] = NULL;
	else
		tmp->key_value[1] = ft_strdup(value);
	tmp->key_value[2] = NULL;
	tmp->visible = visable;
	tmp->next = NULL;
	return (tmp);
}
