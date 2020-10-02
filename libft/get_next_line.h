/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 14:44:37 by drina             #+#    #+#             */
/*   Updated: 2020/10/02 19:28:03 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 1
# include <stdlib.h>
# include <unistd.h>
#include "../lmidori/parser.h"

int		get_next_line(int fd, char **line);
int		ft_strlen_gnl(char *list);
char	*ft_strdup_gnl(char *last_list);
char	*ft_strjoin_gnl(char *line, char *list);
char	*ft_strchr_gnl(char *line, int c);

#endif
