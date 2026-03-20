/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 16:20:00 by metaskin          #+#    #+#             */
/*   Updated: 2026/03/20 18:54:12 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

void	check_numbers(char **args)
{
	int		i;
	long	number;

	i = 0;
	while (args[i])
	{
		// validate lexical number form first
		if (!is_numstr(args[i]))
			error();
		number = ft_atol(args[i]);
		// enforce 32 bit signed integer range
		if (!is_intranger_range(number))
			error();
		i++;
	}
	// check for duplicate values
	if (has_dup(args))
		error();
}

int	read_args(int argc, char **argv, t_flags *flag, t_parse *parse)
{
	int	start;

	parse->args = NULL;
	parse->must_free = 0;
	if (argc < 2)
		return (0);
	// initialize runtime flags before parsing argv
	default_flag(flag);
	if (handle_flags(argc, argv, flag, &start))
		error();
	if (start >= argc)
		return (0);
	if (argc - start == 1)
	{
		// "1 2 3" style: split into tokens
		parse->args = split(argv[start]);
		if (!parse->args || !(parse->args[0]))
			error();
		parse->must_free = 1;
	}
	else
	{
		// "1 2 3" style from argv: already tokenized
		parse->args = argv + start;
		parse->must_free = 0;
	}
	check_numbers(parse->args);
	return (1);
}
