/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:22:26 by metaskin          #+#    #+#             */
/*   Updated: 2026/03/14 01:21:17 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	int		i;
	long	number;
	char	**args;

	if (argc < 2)
		return (0);
	if (argc == 2)
		args = split(argv[1]);
	else
		args = argv + 1;
	i = 0;
	while (args[i] != NULL)
	{
		if (is_numstr(args[i]) == 0)
			error();
		number = ft_atol(args[i]);
		if (is_intrange(number) == 0)
			error();
		i++;
	}
	if (argc == 2)
		free_split(args);
	return (0);
}
