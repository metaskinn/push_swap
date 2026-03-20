/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:22:26 by metaskin          #+#    #+#             */
/*   Updated: 2026/03/20 20:29:57 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "push_swap.h"

int	main(int argc, char **argv)
{
	t_program	program;

	if (!read_args(argc, argv, &program.flag, &program.parse))
		return (0);
	create_stack(&program.a);
	create_stack(&program.b);
	stack_build(&program.a, program.parse.args);
	// If applied algorithms will work HERE
	clear_stack(&program.a);
	clear_stack(&program.b);
	// free ONLY when args came from split()
	if (program.parse.must_free)
		free_split(program.parse.args);
	return (0);
}
