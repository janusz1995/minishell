/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 19:52:51 by lmidori           #+#    #+#             */
/*   Updated: 2020/10/06 19:01:51 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void		cmd_pwd(void)
{
	char	*pwd;

	g_error = 0;
	pwd = getcwd(NULL, 0);
	ft_putstr_fd(pwd, 1);
	write(1, "\n", 1);
	free(pwd);
}
