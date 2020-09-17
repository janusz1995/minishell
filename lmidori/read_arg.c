/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 22:52:29 by lmidori           #+#    #+#             */
/*   Updated: 2020/09/15 21:41:21 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"


int			read_special_char(char *str, t_list_args **list)
{
	char	*out;
	int		i;

	i = 0;
	if (str[i] == '>' && str[i + 1] == '>')
	{
		if ((out = (char *)malloc(sizeof(char) * 3)) == NULL)
			return (-1);
		out[0] = '>';
		out[1] = '>';
		out[2] = '\0';
	}
	else
	{
		if ((out = (char *)malloc(sizeof(char) * 2)) == NULL)
			return (-1);
		out[0] = *str;
		out[1] = '\0';
	}
	ft_lstadd_back_arg(list, ft_lstnew_arg(out, 1));
	return (ft_strlen(out));
}
