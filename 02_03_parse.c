/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_03_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 16:20:00 by metaskin          #+#    #+#             */
/*   Updated: 2026/04/26 05:02:04 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	parse_joined_args(int argc, char **argv, int start, t_parse *parse)
{
	char	*joined;

	joined = join_args(argv, start, argc);
	if (!joined)
		error_cleanup(parse);
	parse->args = split(joined);
	parse->must_free = 1;
	free(joined);
	if (!parse->args || !(parse->args[0]))
		error_cleanup(parse);
	return (1);
}

static int	parse_single_arg(char **argv, int start, t_parse *parse)
{
	parse->args = split(argv[start]);
	parse->must_free = 1;
	if (!parse->args || !(parse->args[0]))
		error_cleanup(parse);
	return (1);
}

static int	parse_multi_arg(int argc, char **argv, int start, t_parse *parse)
{
	t_wspace_check	ws;

	ws = check_argv_wspace(argv, start, argc);
	if (ws.count == -1)
		error_cleanup(parse);
	if (ws.count == 0)
	{
		parse->args = argv + start;
		parse->must_free = 0;
	}
	else
		parse_joined_args(argc, argv, start, parse);
	return (1);
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
		error_cleanup(parse);
	if (start >= argc)
		return (0);
	if (argc - start == 1)
		parse_single_arg(argv, start, parse);
	else
		parse_multi_arg(argc, argv, start, parse);
	if (check_numbers(parse->args))
		error_cleanup(parse);
	return (1);
}
