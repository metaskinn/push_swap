/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:22:26 by metaskin          #+#    #+#             */
/*   Updated: 2026/03/14 08:06:05 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_program	program;

	if (args_input(argc, argv, &program.flag, &program.parse) == 0)
		return (0);
	stack_init(&program.a);
	stack_init(&program.b);
	stack_build_from_args(&program.a, program.parse.args);
	program.bench.enabled = program.flag.bench;
	program.bench.total_ops = 0;
	program.bench.disorder = 0;
	program.bench.strategy = program.flag.which_algo;
	stack_clear(&program.a);
	stack_clear(&program.b);
	if (program.parse.need_free)
		free_split(program.parse.args);
	return (0);
}
