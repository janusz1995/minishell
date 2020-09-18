
#include "minishelldrina.h"

void		get_home_dir(t_env **head, char **str)
{
	t_env	*tmp;

	tmp = (*head);
	while (tmp->next != NULL)
	{
		if ((ft_strncmp(tmp->key_value[0], "HOME", 4)) == 0)
			*str = tmp->key_value[1];
		tmp = tmp->next;
	}
}
