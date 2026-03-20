/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 16:20:00 by metaskin          #+#    #+#             */
/*   Updated: 2026/03/20 19:47:24 by metaskin         ###   ########.fr       */
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
	int	wspace_count;
	int	wspace_index;

	if (check_argv_wspace(argv, start, argc, &wspace_count, &wspace_index))
		error();
	if (wspace_count == 0)
	{
		parse->args = argv + start;
		parse->must_free = 0;
	}
	else if (wspace_count == 1 && !has_edge_wspace(argv[wspace_index]))
		parse_joined_args(argc, argv, start, parse);
	else
		error();
	return (1);
}

void	check_numbers(char **args)
{
	int		i;
	long	number;

	i = 0;
	while (args[i])
	{
		// once bicimi dogru mu
		if (!is_numstr(args[i]))
			error();
		number = ft_atol(args[i]);
		// 32 bit int araligi
		if (!is_intranger_range(number))
			error();
		i++;
	}
	// tekrar eden deger var mi
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
		parse_single_arg(argv, start, parse);
	else
		parse_multi_arg(argc, argv, start, parse);
	check_numbers(parse->args);
	return (1);
}
