
#include "parser.h"

void		no_system_cmd(t_head_struct *head_struct, char **str, t_list_args *args, int flag)
{
	int i;

	i = 0;
	if (str[0] && (ft_strncmp(str[0], "cd", ft_strlen(str[0]) + 1) == 0))
		cmd_cd(str, head_struct->env);
	else if (str[0] && (ft_strncmp(str[0], "pwd", ft_strlen(str[0]) + 1)) == 0)
		cmd_pwd(head_struct->env);
	else if (str[0] && (ft_strncmp(str[0], "env", ft_strlen(str[0]) + 1) == 0))
		cmd_env(head_struct->env);
	else if (str[0] && (ft_strncmp(str[0], "unset", ft_strlen(str[0]) + 1) == 0))
	{
		if (flag)
		{
			while (str[i])
				cmd_unset(&(head_struct->env), str[i++]);
		}
		else
			cmd_unset(&(head_struct->env), str[1]);
	}
	else if (str[0] && (ft_strncmp(str[0], "export", ft_strlen(str[0]) + 1) == 0))
		cmd_export(&(head_struct->env), args);
	else if (str[0] && (ft_strncmp(str[0], "echo", ft_strlen(str[0]) + 1) == 0))
		cmd_echo(args);
	else if (str[0] && (ft_strncmp(str[0], "exit", ft_strlen(str[0]) + 1) == 0))
		exit_cmd(str);
}
