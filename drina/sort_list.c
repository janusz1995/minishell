
#include "minishelldrina.h"

static	void		swap_two_elem(t_env **head, t_env *one, t_env *two)
{
	t_env	*tmp;
	t_env	*root;

	root = *head;
	if (root == one)
	{
		tmp = two->next;
		two->next = one;
		one->next = tmp;
		(*head) = two;
	}
	else
	{
		while (root->next != one)
			root = root->next;
		tmp = two->next;
		two->next = one;
		one->next = tmp;
		root->next = two;
	}
}

void				sort_list(t_env **head)
{
	t_env	*tmp;
	int		flag;

	flag = 1;
	while (flag)
	{
		flag = 0;
		tmp = (*head);
		while (tmp->next != NULL)
		{
			if ((ft_strncmp(tmp->key_value[0], tmp->next->key_value[0], ft_strlen(tmp->key_value[0]))) > 0)
			{
				swap_two_elem(head, tmp, tmp->next);
				flag = 1;
			}
			else
				tmp = tmp->next;
		}
	}

}
