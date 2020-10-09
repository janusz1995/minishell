
#include "parser.h"
#include "minishell.h"

//void 		check_token(t_head_struct *head_struct)
//{
//	ft_putstr_fd("syntax error near unexpected token `", 1);
//	if (*head_struct->last_token == '|' && *head_struct->all.spec != '|')
//	{
//		ft_putstr_fd(head_struct->last_token, 1);
//		// syntax error near unexpected token `|';
//	}
//	else if (*head_struct->last_token == '>' && (*head_struct->all.spec == ';' || *head_struct->all.spec == '<'))
//	{
//		ft_putstr_fd(head_struct->last_token, 1);
//		// syntax error near unexpected token `<'
//		// syntax error near unexpected token `;'
//	}
//	else if (*head_struct->last_token == *head_struct->all.spec &&
//	(*head_struct->last_token != '<' || *head_struct->last_token != '>'))
//	{
//		ft_putstr_fd(head_struct->last_token, 1);
//		ft_putstr_fd(head_struct->all.spec, 1);
//		// syntax error near unexpected token `||'
//		// syntax error near unexpected token `;;'
//	}
//	else
//		ft_putstr_fd("newline", 1);
//
//	ft_putstr_fd("'", 1);
//	ft_putstr_fd("\n", 1);
//
//}

void 		start_shell(t_all *all, t_head_struct *head_struct)
{
	char		**str;

//	if (head_struct->last_token != NULL)
//	{
//
//		if (head_struct->all.args == NULL && head_struct->all.spec && (*head_struct->all.spec == '|'
//		|| *head_struct->all.spec == '<' || *head_struct->all.spec == '>'
//		|| *head_struct->all.spec == ';'))
//		{
//			check_token(head_struct);
//			free(head_struct->last_token);
//			head_struct->last_token = NULL;
//			return ;
//		}
//		free(head_struct->last_token);
//		head_struct->last_token = NULL;
//	}
//	if (head_struct->last_token == NULL && head_struct->all.spec)
//		head_struct->last_token = ft_strdup(head_struct->all.spec);

	str = get_arg(&(all->args));
	if (*str[0] == '\0' && all->spec == NULL) // leak
		return;
	if (head_struct->flag_error == 0)
		select_cmd(head_struct, str, head_struct->all.args);
	free(str);
}

int			add_new_env(t_head_struct *head_struct, char **str)
{
	t_list_args *arg;
	int			flag;
	int			i;

	i = 0;
	flag = 1;
	arg = head_struct->all.args;
	while (arg && arg->spec_flag == 2)
	{
		if (!(flag = check_name(arg->content, '=')))
			break;
		arg = arg->next;
		i++;
	}
	if (!arg && (head_struct->all.spec == NULL || *head_struct->all.spec != '|'))
	{
		arg = head_struct->all.args;
		while (arg != NULL)
		{
			if (!(init_env(arg->content, &(head_struct->env))))
				return (-1);
			arg = arg->next;
		}
	}
	else if (!flag || (arg && arg->spec_flag != 2))
	{
		head_struct->all.equal = 0;
		select_cmd(head_struct, &str[i], arg);
	}
	return (1);
}

void		start_redirect(t_head_struct *head_struct, char **str, t_list_args *args)
{
	t_list_args		*tmp;

	if (head_struct->copy_all != NULL)
	{
		tmp = args;
		while (tmp && tmp->next != NULL)
		{
			ft_lstadd_back_arg(&(head_struct->copy_all->args),
							ft_lstnew_arg(ft_strdup(tmp->next->content), tmp->next->spec_flag));
			tmp = tmp->next;
		}
	}
	redirect(head_struct, str, args);
}

void 		select_cmd(t_head_struct *head_struct, char **str, t_list_args *args)
{
	head_struct->flag_pipe = 0;
	if (head_struct->all.equal == 1)
		add_new_env(head_struct, str);
	if (head_struct->flag_redir || (head_struct->all.spec && (*(head_struct->all.spec) == '>' ||
		(ft_strncmp(head_struct->all.spec, ">>", 3) == 0) || *(head_struct->all.spec) == '<')))
		start_redirect(head_struct, str, args);
	else if (head_struct->all.spec && *(head_struct->all.spec) == '|')
	{
		if (args != NULL)
			cmd_pipe(head_struct, str, args, 0);
	}
	else
		commands(head_struct, str, args, 1);
}
