/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 18:22:57 by metaskin          #+#    #+#             */
/*   Updated: 2026/04/02 02:46:03 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGO_H
# define ALGO_H

# include "parser.h"
# include "push_swap.h"
# include "stack.h"
# include <stdlib.h>

double	compute_disorder(t_stack head);
void	simple_sort(t_stack *a, t_stack *b, t_flags *flag);
void	medium_sort(t_stack *a, t_stack *b, t_flags *flag);
void	complex_sort(t_stack *a, t_stack *b, t_flags *flag);
void	adaptive_sort(t_stack *a, t_stack *b, t_flags *flag);
void	run_selected_algo(t_program *program);
void	print_benchmark(t_program *program);
void	push_back_to_a(t_stack *a, t_stack *b, t_flags *flag);
int		find_max_pos(t_stack *b);
void	complex_assign_indices(t_stack *a);
int		complex_max_bits_for_size(int size);
void	complex_run_radix_pass(t_stack *a, t_stack *b, t_flags *flag, int bit);

#endif
