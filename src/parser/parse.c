/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 16:20:00 by metaskin          #+#    #+#             */
/*   Updated: 2026/04/02 01:54:05 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

static int	parse_joined_args(int argc, char **argv, int start, t_parse *parse)
{
	char	*joined;

	joined = join_args(argv, start, argc);
	if (!joined)
		error();
	parse->args = split(joined);
	free(joined);
	if (!parse->args || !(parse->args[0]))
		error();
	parse->must_free = 1;
	return (1);
}

static int	parse_single_arg(char **argv, int start, t_parse *parse)
{
	parse->args = split(argv[start]);
	if (!parse->args || !(parse->args[0]))
		error();
	parse->must_free = 1;
	return (1);
}

static int	parse_multi_arg(int argc, char **argv, int start, t_parse *parse)
{
	t_wspace_check	ws;

	ws = check_argv_wspace(argv, start, argc);
	if (ws.count == -1)
		error();
	if (ws.count == 0)
	{
		parse->args = argv + start;
		parse->must_free = 0;
	}
	else if (ws.count == 1 && !has_edge_wspace(argv[ws.index]))
		parse_joined_args(argc, argv, start, parse);
	else
		error();
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
		error();
	if (start >= argc)
		return (0);
	if (argc - start == 1)
		parse_single_arg(argv, start, parse);
	else
		parse_multi_arg(argc, argv, start, parse);
	check_numbers(parse->args);
	return (1);
}
