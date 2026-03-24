/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:22:26 by metaskin          #+#    #+#             */
/*   Updated: 2026/03/25 01:10:20 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_program	program;
	float			conpute_d;

	if (!read_args(argc, argv, &program.flag, &program.parse))
		return (0);
	create_stack(&program.a);
	create_stack(&program.b);
	stack_build(&program.a, program.parse.args);
	// If applied algorithms will work HERE
	conpute_d = compute_disorder(program.a);
	printf("%f",conpute_d);
	clear_stack(&program.a);
	clear_stack(&program.b);
	// free ONLY when args came from split()
	if (program.parse.must_free)
		free_split(program.parse.args);
	return (0);
}
