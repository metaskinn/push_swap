/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selector.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 07:35:00 by metaskin          #+#    #+#             */
/*   Updated: 2026/03/28 19:59:34 by metaskin         ###   ########.fr       */
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
	else
		medium_sort(&program->a, &program->b, &program->flag);
}
