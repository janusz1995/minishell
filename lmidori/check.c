
#include "parser.h"

int			check_name(char *var, char ch)
{
	int		i;

	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (0);
	i = -1;
	while (var[++i] != ch && var[i] != '\0')
	{
		if (!ft_isdigit(var[i]) && !ft_isalpha(var[i]) && var[i] != '_')
			return (0);
	}
	return (i);
}

int 		check_cond(char *str)
{
	return ((ft_strncmp(str, "cd", ft_strlen(str) + 1) == 0) ||
			(ft_strncmp(str, "pwd", ft_strlen(str) + 1) == 0) ||
			(ft_strncmp(str, "env", ft_strlen(str) + 1) == 0) ||
			(ft_strncmp(str, "unset", ft_strlen(str) + 1) == 0) ||
			(ft_strncmp(str, "echo", ft_strlen(str) + 1) == 0) ||
			(ft_strncmp(str, "exit", ft_strlen(str) + 1) == 0) ||
			(ft_strncmp(str, "export", ft_strlen(str) + 1) == 0));
}
