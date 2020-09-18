
#include "minishelldrina.h"

void 		cmd_pwd(t_env *head)
{
	t_env *tmp;

	tmp = head;
	while (tmp->next != NULL)
	{
		if ((ft_strncmp(tmp->key_value[0], "PWD=", ft_strlen(tmp->key_value[0])) == 0))
		{
			ft_putstr_fd(tmp->key_value[1], 1);
			write(1, "\n" , 1);
			break ;
		}
		tmp = tmp->next;
	}
}
