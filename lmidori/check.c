/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 17:46:07 by lmidori           #+#    #+#             */
/*   Updated: 2020/10/03 22:55:36 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		check_cond(char *str)
{
	return ((ft_strncmp(str, "cd", ft_strlen(str) + 1) == 0) ||
			(ft_strncmp(str, "pwd", ft_strlen(str) + 1) == 0) ||
			(ft_strncmp(str, "env", ft_strlen(str) + 1) == 0) ||
			(ft_strncmp(str, "unset", ft_strlen(str) + 1) == 0) ||
			(ft_strncmp(str, "echo", ft_strlen(str) + 1) == 0) ||
			(ft_strncmp(str, "exit", ft_strlen(str) + 1) == 0) ||
			(ft_strncmp(str, "export", ft_strlen(str) + 1) == 0));
}
