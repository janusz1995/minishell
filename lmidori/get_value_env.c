
#include "parser.h"

char		*get_value_env(char *var)
{
	char	*out;
	int		i;
	int		len;

	len = ft_strlen(var);
	if (!(out = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = -1;
	out[len] = '\0';
	while (var[++i] != '\0')
		out[i] = var[i];
	return (out);
}
