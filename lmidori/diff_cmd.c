
#include "parser.h"

void		diff_cmd(char *str, char **path_bin, char **envp, char **str2)
{
	DIR				*dir;
	struct dirent	*entry;
	int				i;
	int				flag;

	i = 0;
	flag = 0;
	while (path_bin[i])
	{
		dir = opendir(path_bin[i]);
		while ((entry = readdir(dir)) != NULL)
		{
			if ((ft_strncmp(str, entry->d_name, ft_strlen(str) + 1)) == 0)
			{
				start_programm(str, path_bin[i], envp, str2);
				flag = 1;
				break ;
			}
		}
		closedir(dir);
		i++;
		if (flag)
			break ;
	}
	if (flag == 0)
		start_programm(str, path_bin[i], envp, str2);
}
