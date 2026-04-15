/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asobolev <asobolev@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:22:26 by metaskin          #+#    #+#             */
/*   Updated: 2026/04/15 05:46:43 by asobolev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algo.h"

int	main(int argc, char **argv)
{
	t_program	program;

	if (!read_args(argc, argv, &program.flag, &program.parse))
		return (0);
	create_stack(&program.a);
	create_stack(&program.b);
	stack_build(&program.a, program.parse.args);
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
