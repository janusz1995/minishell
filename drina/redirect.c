
#include "parser.h"
#include <sys/types.h>
#include <sys/stat.h>

//int		str_error(t_head_struct *head_struct, char *str, int flag)
//{
//	head_struct->flag_error = 1;
//	g_error = errno;
//	ft_putstr_fd("minishell: ", 2);
//	ft_putstr_fd(str, 2);
//	ft_putstr_fd(": Permission denied\n", 2);
//	head_struct->flag_redir = 0;
//	free_list_copy(head_struct);
//	return (0);
//}

int		check_and_create_void_file(t_head_struct *head_struct, char **str)
{
	if (head_struct->last_spec &&
				ft_strncmp(head_struct->last_spec, ">>", 3) == 0)
	{
		if ((head_struct->fd_redir = open(str[0],
								O_CREAT | O_APPEND | O_WRONLY, 0644)) < 0)
			return (error_and_free(head_struct, str[0]));
	}
	else if (head_struct->last_spec && *(head_struct->last_spec) == '>')
	{
		if ((head_struct->fd_redir = open(str[0],
								O_CREAT | O_WRONLY | O_TRUNC, 0644)) < 0)
			return (0);
	}
	else if (head_struct->last_spec && *(head_struct->last_spec) == '<')
	{
		if ((head_struct->fd_redir = open(str[0], O_RDONLY)) < 0)
			return (error_and_free(head_struct, str[0]));
	}
	last_spec_free(head_struct);
	if (head_struct->all.spec && head_struct->last_spec == NULL)
		head_struct->last_spec = ft_strdup(head_struct->all.spec);
	close(head_struct->fd_redir);
	return (1);
}

int		create_file(t_head_struct *head_struct, char **str)
{
	if (head_struct->copy_all->spec && *(head_struct->copy_all->spec) == '<')
	{
		if ((head_struct->fd_redir = open(str[0], O_RDONLY)) < 0)
			return (error_and_free(head_struct, str[0]));
	}
	else if (head_struct->copy_all->spec &&
					ft_strncmp(head_struct->copy_all->spec, ">>", 3) == 0)
	{
		if ((head_struct->fd_redir = open(str[0],
									O_CREAT | O_APPEND | O_WRONLY, 0644)) < 0)
			return (error_and_free(head_struct, str[0]));
	}
	else
	{
		if ((head_struct->fd_redir = open(str[0],
									O_CREAT | O_WRONLY | O_TRUNC, 0644)) < 0)
			return (error_and_free(head_struct, str[0]));
	}
	return (1);
}

void	start_command(t_head_struct *head_struct)
{
	head_struct->new_args = get_arg((&head_struct->copy_all->args));
	if (head_struct->all.spec && *(head_struct->all.spec) == '|')
		cmd_pipe(head_struct, head_struct->new_args,
					head_struct->copy_all->args, 1);
	else
	{
		if (head_struct->copy_all->spec &&
					*(head_struct->copy_all->spec) == '<')
			dup2(head_struct->fd_redir, 0);
		else
			dup2(head_struct->fd_redir, 1);
		if (head_struct->copy_all->args != NULL)
			commands(head_struct, head_struct->new_args,
						head_struct->copy_all->args, 1);
	}
	close(head_struct->fd_redir);
	free_double_arr(head_struct->new_args);
	free_list_copy(head_struct);
}

void	redirect(t_head_struct *head_struct, char **str, t_list_args *args)
{
	if (head_struct->copy_all == NULL)
	{
		if (head_struct->all.spec && head_struct->last_spec == NULL)
			head_struct->last_spec = ft_strdup(head_struct->all.spec);
		head_struct->copy_all = malloc(sizeof(t_all));
		if (!head_struct->copy_all)
			return ;
		get_copy_all(&head_struct->all, head_struct->copy_all, args);
		head_struct->flag_redir = 1;
	}
	else if (head_struct->all.spec && (*(head_struct->all.spec) == '>' ||
				ft_strncmp(head_struct->all.spec, ">>", 3) == 0 ||
					*(head_struct->all.spec) == '<'))
	{
		if ((check_and_create_void_file(head_struct, str)) == 0)
			return ;
	}
	else
	{
		head_struct->flag_redir = 0;
		if (check_last_spec(head_struct, str[0]) == 0 ||
					create_file(head_struct, str) == 0)
			return ;
		start_command(head_struct);
	}
}
