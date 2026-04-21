/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_03_parse_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 19:27:00 by metaskin          #+#    #+#             */
/*   Updated: 2026/04/16 13:54:02 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	has_wspace_char(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (is_wspace(s[i]))
			return (1);
		i++;
	}
	return (0);
}

int	is_empty_token(char *s)
{
	int	i;

	i = 0;
	if (!s[0])
		return (1);
	while (s[i])
	{
		if (!is_wspace(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	has_edge_wspace(char *s)
{
	int	len;

	if (!s[0])
		return (1);
	if (is_wspace(s[0]))
		return (1);
	len = (int)ft_strlen(s);
	if (is_wspace(s[len - 1]))
		return (1);
	return (0);
}
