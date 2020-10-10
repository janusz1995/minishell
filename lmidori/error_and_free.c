/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 18:10:31 by lmidori           #+#    #+#             */
/*   Updated: 2020/10/10 18:10:35 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		error_and_free(t_head_struct *head_struct, char *str)
{
	head_struct->flag_error = 1;
	g_error = errno;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	if (errno == 13)
		ft_putstr_fd(": Permission denied\n", 2);
	else if (errno == 2)
		ft_putstr_fd(": No such file or directory\n", 2);
	head_struct->flag_redir = 0;
	free_list_copy(head_struct);
	ft_putnbr_fd(errno, 1);
	write(1, "\n", 1);
	return (0);
}
