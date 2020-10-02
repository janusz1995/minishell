/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xmalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 18:00:47 by lmidori           #+#    #+#             */
/*   Updated: 2020/10/02 19:09:22 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void		*xmalloc(size_t __size)
{
	void	*tmp;

	tmp = malloc(__size);
	if (!tmp)
	{
		ft_putstr_fd("Error: The memory could not be allocated\n", 1);
		exit(2);
	}
	return (tmp);
}
