
#include "parser.h"

char		*get_name_env(char *var, char ch)
{
	char	*name;
	int		i;

	if (!(i = check_name(var, ch)))
		return (NULL);
	if (!(name = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	name[i] = '\0';
	i = 0;
	while (var[i] != ch && var[i] != '\0')
	{
		name[i] = var[i];
		i++;
	}
	return (name);
}
