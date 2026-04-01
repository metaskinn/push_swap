/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selector.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 07:35:00 by metaskin          #+#    #+#             */
/*   Updated: 2026/04/02 01:53:36 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algo.h"
#include "push_swap.h"

void	run_selected_algo(t_program *program)
{
	if (program->flag.which_algo == SIMPLE)
		simple_sort(&program->a, &program->b, &program->flag);
	else if (program->flag.which_algo == MEDIUM)
		medium_sort(&program->a, &program->b, &program->flag);
	else if (program->flag.which_algo == COMPLEX)
		complex_sort(&program->a, &program->b, &program->flag);
	else if (program->flag.which_algo == ADAPTIVE)
		adaptive_sort(&program->a, &program->b, &program->flag);
	else
		adaptive_sort(&program->a, &program->b, &program->flag);
}
