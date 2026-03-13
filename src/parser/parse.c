/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 16:20:00 by metaskin          #+#    #+#             */
/*   Updated: 2026/03/14 02:34:35 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	validate_args(char **args)
{
	int		i;
	long	number;

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
	if (has_dup(args))
		error();
}

int	parse_input(int argc, char **argv, t_flags *flag, char ***args,
		int *need_free)
{
	int	start;

	*args = NULL;
	*need_free = 0;
	init_flags(flag);
	if (parse_flags(argc, argv, flag, &start) != 0)
		error();
	if (start >= argc)
		return (0);
	if (argc - start == 1)
	{
		*args = split(argv[start]);
		if (!*args || !(*args)[0])
			error();
		*need_free = 1;
	}
	else
		*args = argv + start;
	validate_args(*args);
	return (1);
}
