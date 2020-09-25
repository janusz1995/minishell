
#include "parser.h"

int			find_in_env(t_env **env, char *name)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key_value[0], name, ft_strlen(tmp->key_value[0]) + 1) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
