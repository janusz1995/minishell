
#include "minishell.h"

void 		add_equal(t_env **head)
{
	t_env	*tmp;
	char	*str;

	tmp = (*head);
	while (tmp->next != NULL)
	{
		str = tmp->key_value[0];
		tmp->key_value[0] = ft_strjoin(tmp->key_value[0], "=");
		free(str);
		tmp = tmp->next;
	}
}
