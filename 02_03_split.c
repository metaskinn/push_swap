/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_03_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 22:30:58 by asobolev          #+#    #+#             */
/*   Updated: 2026/04/16 13:54:31 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

int	is_wspace(char c)
{
	if (c == '\r' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == ' ')
		return (1);
	return (0);
}

static int	get_wordcount(char const *s)
{
	int	wordcount;

	wordcount = 0;
	while (*s)
	{
		while (*s && is_wspace(*s) == 1)
			s++;
		if (*s)
			wordcount++;
		while (*s && is_wspace(*s) == 0)
			s++;
	}
	return (wordcount);
}

void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static char	*next_token(char **s)
{
	int	len;

	while (is_wspace(**s))
		(*s)++;
	len = 0;
	while ((*s)[len] && !is_wspace((*s)[len]))
		len++;
	return (ft_substr(*s, 0, len));
}

char	**split(char *s)
{
	int		wordcount;
	int		i;
	char	**ptr;

	if (!s)
		return (NULL);
	wordcount = get_wordcount(s);
	i = 0;
	ptr = ft_calloc((wordcount + 1), sizeof(char *));
	if (!ptr)
		return (NULL);
	while (i < wordcount)
	{
		ptr[i++] = next_token(&s);
		if (!ptr[i - 1])
			return (free_split(ptr), NULL);
		s += ft_strlen(ptr[i - 1]);
	}
	return (ptr);
}
