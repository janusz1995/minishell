/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drina <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 15:34:41 by drina             #+#    #+#             */
/*   Updated: 2020/05/14 15:06:07 by drina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		full_massiv(char *s1, const char *s2, size_t start, size_t end)
{
	size_t	count;

	count = 0;
	while (start < end)
	{
		s1[count] = s2[start];
		start++;
		count++;
	}
	s1[count] = '\0';
}

static void		free_memory(char **list, size_t words)
{
	size_t	count;

	count = 0;
	while (count < words)
	{
		free(list[count]);
		count++;
	}
	free(list);
}

static size_t	words_count(const char *list, char c)
{
	size_t	count;
	size_t	words;

	words = 0;
	count = 0;
	while (list[count] == c && list[count] != '\0')
		count++;
	while (list[count] != '\0')
	{
		while (list[count] != c && list[count] != '\0')
			count++;
		words++;
		while (list[count] == c && list[count] != '\0')
			count++;
	}
	return (words);
}

static char		**full_list(const char *s, char c, char **list, size_t count_w)
{
	size_t	count;
	size_t	words;
	size_t	len_word;

	words = 0;
	count = 0;
	len_word = 0;
	while (s[count] != '\0' && count_w > words)
	{
		while (s[count] == c && s[count] != '\0')
			count++;
		len_word = count;
		while (s[len_word] != c && s[len_word] != '\0')
			len_word++;
		list[words] = (char *)malloc(((len_word - count) + 1) * sizeof(char));
		if (!list[words])
		{
			free_memory(list, words);
			return (NULL);
		}
		full_massiv(list[words], s, count, len_word);
		words++;
		count = len_word;
	}
	return (list);
}

char			**ft_split(char const *s, char c)
{
	size_t	words;
	char	**list;

	if (!s)
		return (NULL);
	words = words_count(s, c);
	list = (char **)malloc((words + 1) * sizeof(char *));
	if (!list)
		return (NULL);
	list = full_list(s, c, list, words);
	if (!list)
		return (NULL);
	list[words] = NULL;
	return (list);
}
