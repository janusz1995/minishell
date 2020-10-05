/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 21:19:40 by lmidori           #+#    #+#             */
/*   Updated: 2020/10/05 23:27:10 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_env				*new_key_value(char *str, int visible)
{
	t_env			*new_elem;
	int				count;

	new_elem = (t_env*)malloc(sizeof(t_env));
	if (!new_elem)
		return (NULL);
	count = 0;
	while (str[count] != '\0' && str[count] != '=')
		count++;
	str[count] = '\0';
	if (!(new_elem->key_value = (char **)malloc(sizeof(char *) * 3)))
		return (NULL);
	new_elem->key_value[0] = ft_strdup(str);
	if (str[count + 1] == '\0')
		new_elem->key_value[1] = ft_strdup("");
	else
		new_elem->key_value[1] = ft_strdup(&str[count + 1]);
	new_elem->key_value[2] = NULL;
	new_elem->visible = visible;
	new_elem->next = NULL;
	return (new_elem);
}

void				all_envp(t_env **env, char **envp)
{
	int				i;
	int				flag;

	i = 0;
	flag = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp("OLDPWD", envp[i], 6) == 0)
			flag = 1;
		add_back(env, new_key_value(envp[i], 1));
		i++;
	}
}

void				add_back(t_env **head, t_env *new)
{
	t_env			*save_head;

	save_head = (*head);
	if (save_head == NULL)
		(*head) = new;
	else
	{
		while (save_head->next != NULL)
			save_head = save_head->next;
		save_head->next = new;
	}
}

int					lstsize_env(t_env *lst, int flag)
{
	int				len;

	len = 0;
	if (!lst)
		return (0);
	while (lst != NULL)
	{
		if (lst->visible == flag)
			len++;
		lst = lst->next;
	}
	return (len);
}

t_env				*lst_new_env(char *name, char *value, int visable)
{
	t_env			*tmp;

	if (!(tmp = (t_env *)malloc(sizeof(t_env))))
		return (NULL);
	if (!(tmp->key_value = (char **)malloc(sizeof(char *) * 3)))
		return (NULL);
	tmp->key_value[0] = ft_strdup(name);
	if (value == NULL)
		tmp->key_value[1] = NULL;
	else
		tmp->key_value[1] = ft_strdup(value);
	tmp->key_value[2] = NULL;
	tmp->visible = visable;
	tmp->next = NULL;
	return (tmp);
}
