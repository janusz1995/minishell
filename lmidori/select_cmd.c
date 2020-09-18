
#include "parser.h"

void 	select_cmd(t_all *all)
{
	/// Need change str
	if (str2[0] && (ft_strncmp(str2[0], "cd", ft_strlen(str2[0])) == 0))
	{
		cmd_cd(str2, tmp);
	}
	else if (str2[0] && (ft_strncmp(str2[0], "pwd", ft_strlen(str2[0]))) == 0)
	{
		cmd_pwd(env);
	}
	else if (str2[0] && (ft_strncmp(str2[0], "env", ft_strlen(str[0])) == 0))
	{
		cmd_env(env);
	}
//		else if (str[0] && (ft_strncmp(str2[0], "export", ft_strlen(str2[0])) == 0))
//		{
//
//		}
	else if (str2[0] && (ft_strncmp(str2[0], "exit", ft_strlen(str2[0]) + 1) == 0))
		exit(0);
	else
		diff_cmd(str2[0], bin, envp, str2);
}