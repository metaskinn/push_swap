/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 18:22:57 by metaskin          #+#    #+#             */
/*   Updated: 2026/04/16 13:55:13 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGO_H
# define ALGO_H

# include "push_swap.h"

double	compute_disorder(t_stack head);
void	simple_sort(t_stack *a, t_stack *b, t_flags *flag);
void	medium_sort(t_stack *a, t_stack *b, t_flags *flag);
void	complex_sort(t_stack *a, t_stack *b, t_flags *flag);
void	adaptive_sort(t_stack *a, t_stack *b, t_flags *flag);
void	run_selected_algo(t_program *program);
void	print_benchmark(t_program *program);
void	push_back_to_a(t_stack *a, t_stack *b, t_flags *flag);
int		find_max_pos(t_stack *b);
int		find_min_pos(t_stack *a);
void	complex_assign_indices(t_stack *a);
int		complex_max_bits_for_size(int size);
void	complex_run_radix_pass(t_stack *a, t_stack *b, t_flags *flag, int bit);
void	five_or_less_sort(t_stack *a, t_stack *b, t_flags *flag);
void	rotate_to_min(t_stack *a, int pos, t_flags *flag);
int		is_sorted_stack(t_stack *a);
#endif
