/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drina <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 14:44:37 by drina             #+#    #+#             */
/*   Updated: 2020/07/23 15:10:10 by drina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 32
# include <stdlib.h>
# include <unistd.h>

int		get_next_line(int fd, char **line);
int		ft_strlen_gnl(char *list);
char	*ft_strdup_gnl(char *last_list);
char	*ft_strjoin_gnl(char *line, char *list);
char	*ft_strchr_gnl(char *line, int c);

#endif
