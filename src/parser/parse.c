/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 16:20:00 by metaskin          #+#    #+#             */
/*   Updated: 2026/03/20 18:32:42 by metaskin         ###   ########.fr       */
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
		if (!is_numstr(args[i]))
			error();
		number = ft_atol(args[i]);
		if (!is_intranger_range(number))
			error();
		i++;
	}
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
	default_flag(flag);
	if (handle_flags(argc, argv, flag, &start))
		error();
	if (start >= argc)
		return (0);
	if (argc - start == 1)
	{
		parse->args = split(argv[start]);// Single string input need to split it
		if (!parse->args || !(parse->args[0]))
			error();
		parse->must_free = 1;
	}
	else
	{// Multiarg input already comes tokenized from argv
		parse->args = argv + start;
		parse->must_free = 0;
	}
	check_numbers(parse->args);
	return (1);
}
