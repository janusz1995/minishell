
#include "parser.h"

void		print_export(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (tmp->visible != 0)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(tmp->key_value[0], 1);
			if (tmp->key_value[1] != NULL)
			{
				ft_putstr_fd("=", 1);
				ft_putstr_fd("\"", 1);
				ft_putstr_fd(tmp->key_value[1], 1);
				ft_putstr_fd("\"", 1);
			}
			ft_putstr_fd("\n", 1);
		}
		tmp = tmp->next;
	}
}
