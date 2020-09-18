
#include "minishelldrina.h"

void		all_envp(t_env **env, char **envp)
{
	int i;

	i = 0;
	while (envp[i] != NULL)
	{
		add_back(env, lstnew(envp[i]));
		i++;
	}
}
