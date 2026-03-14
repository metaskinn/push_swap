/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 16:20:00 by metaskin          #+#    #+#             */
/*   Updated: 2026/03/14 06:17:55 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

static void	check_args(char **args)
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

int	args_input(int argc, char **argv, t_flags *flag, t_parse *parse)
{
	int	start;

	parse->args = NULL;
	parse->need_free = 0;
	init_flags(flag);
	if (parse_flags(argc, argv, flag, &start) != 0)
		error();
	if (start >= argc)
		return (0);
	if (argc - start == 1)
	{
		parse->args = split(argv[start]);
		if (!parse->args || !(parse->args[0]))
			error();
		parse->need_free = 1;
	}
	else
		parse->args = argv + start;
	check_args(parse->args);
	return (1);
}
