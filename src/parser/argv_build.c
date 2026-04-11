/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_build.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 00:00:00 by metaskin          #+#    #+#             */
/*   Updated: 2026/04/10 00:00:00 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

char	*join_args(char **argv, int start, int argc)
{
	char	*joined;
	size_t	total;
	int		i;
	int		j;
	int		k;

	total = argc - start - 1;
	i = start;
	while (i < argc)
		total += ft_strlen(argv[i++]);
	joined = ft_calloc(total + 1, sizeof(char));
	if (!joined)
		return (NULL);
	i = start;
	k = 0;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
			joined[k++] = argv[i][j++];
		if (i + 1 < argc)
			joined[k++] = ' ';
		i++;
	}
	return (joined);
}

t_wspace_check	check_argv_wspace(char **argv, int start, int argc)
{
	t_wspace_check	result;
	int				i;

	i = start;
	result.count = 0;
	result.index = -1;
	while (i < argc)
	{
		if (is_empty_token(argv[i]))
		{
			result.count = -1;
			return (result);
		}
		if (has_wspace_char(argv[i]))
		{
			result.count++;
			result.index = i;
		}
		i++;
	}
	return (result);
}
