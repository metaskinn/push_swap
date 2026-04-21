/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:22:26 by metaskin          #+#    #+#             */
/*   Updated: 2026/04/21 15:57:42 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_program	program;

	if (!read_args(argc, argv, &program.flag, &program.parse))
		return (1);
	create_stack(&program.a);
	create_stack(&program.b);
	stack_build(&program.a, program.parse.args, &program.parse);
	program.flag.disorder = compute_disorder(program.a);
	run_selected_algo(&program);
	if (program.flag.bench)
		print_benchmark(&program);
	clear_stack(&program.a);
	clear_stack(&program.b);
	if (program.parse.must_free)
		free_split(program.parse.args);
	return (0);
}
