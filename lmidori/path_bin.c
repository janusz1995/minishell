
#include "minishelldrina.h"

char		**path_bin(t_env **head)
{
	t_env	*tmp;
	char	**str;

	tmp = (*head);
	while (tmp->next != NULL)
	{
		if ((ft_strncmp(tmp->key_value[0], "PATH=", ft_strlen(tmp->key_value[0]))) == 0)
			str = ft_split(tmp->key_value[1], ':');
		tmp = tmp->next;
	}
	return (str);
}
