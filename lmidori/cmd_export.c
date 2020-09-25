
#include "parser.h"
#include "minishell.h"

void		cmd_export(t_env **envp, t_list_args *args)
{
	t_list_args		*tmp;
	char			*name;
	char			*value;

	if (!args->next)
		print_export(envp);
	else
	{
		tmp = args->next;
		while (tmp)
		{
			if (!(name = get_name_env(tmp->content, '=')))
			{
				tmp = tmp->next;
				continue;
			}
			if (find_in_env(envp, name)) // если параметр уже есть в списке env
			{
				if (ft_strchr(tmp->content, '=') != NULL) // если это пример по типу a=123sd
				{
					if (!(value = get_value_env(&(tmp->content[ft_strlen(name) + 1]))))
						return ;
					redact_env(envp, name, value);
					free(value);
				}
				else		// если это параметр по типу afrwg_weg без =
					redact_env(envp, name, NULL);
			}
			else			// если такого нет в списке
			{
				if (ft_strchr(tmp->content, '=') != NULL) // если это пример по типу a=123sd
				{
					if (!(value = get_value_env(&(tmp->content[ft_strlen(name) + 1]))))
						return ;
					add_back(envp, lst_new_env(name, value, 1));
					free(value);
				}
				else		// если это параметр по типу afrwg_weg без =
					add_back(envp, lst_new_env(name, NULL, 1));
			}
			free(name);
			tmp = tmp->next;
		}
	}
}