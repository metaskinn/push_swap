/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asobolev <asobolev@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 22:30:58 by asobolev          #+#    #+#             */
/*   Updated: 2026/03/13 00:16:21 by asobolev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int     white_space(char c)
{
    if (c == '\r' || c == '\t' || c == '\n' || c == '\v' || c == '\f' 
        || c == ' ')
        return(1);
    return(0);
}

static int	get_wordcount(char const *s)
{
	int	wordcount;

	wordcount = 0;
	while (*s)
	{
		while (*s && white_space(*s) == 1)
			s++;
		if (*s)
			wordcount ++;
		while (*s && white_space(*s) == 0)
			s++;
	}
	return (wordcount);
}

static void	freeptr(char **ptr)
{
	int	i;

	if (!ptr)
		return ;
	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

char	**ft_split(char const *s)
{
	int		wordcount;
	int		i;
	int		j;
	char	**ptr;

	if (!s)
		return (NULL);
	wordcount = get_wordcount(s);
	i = 0;
	ptr = malloc((wordcount + 1) * sizeof(char *));
	if (!ptr)
		return (NULL);
	while (i < wordcount)
	{
		while (white_space(*s) == 1)
			s++;
		j = 0;
		while (white_space(s[j]) == 1 && (s[j]) != '\0')
			j++;
		ptr[i++] = ft_substr(s, 0, j);
		if (!ptr[i - 1])
			return (freeptr(ptr), NULL);
		s = s + j;
	}
	return (ptr);
}