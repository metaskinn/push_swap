/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 07:31:00 by metaskin          #+#    #+#             */
/*   Updated: 2026/04/10 04:10:26 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algo.h"

void	complex_sort(t_stack *a, t_stack *b, t_flags *flag)
{
	int	max_bits;
	int	bit;

	if (!a || !b)
		return ;
	if (a->size < 2 || compute_disorder(*a) == 0)
		return ;
	complex_assign_indices(a);
	max_bits = complex_max_bits_for_size(a->size);
	bit = 0;
	while (bit < max_bits)
	{
		complex_run_radix_pass(a, b, flag, bit);
		bit++;
	}
}
