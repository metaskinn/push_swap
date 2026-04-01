/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 03:55:00 by metaskin          #+#    #+#             */
/*   Updated: 2026/04/02 02:46:55 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algo.h"
#include "ops.h"

void	complex_assign_indices(t_stack *a)
{
	t_node	*cur;
	t_node	*cmp;
	int		rank;

	cur = a->top;
	while (cur)
	{
		rank = 0;
		cmp = a->top;
		while (cmp)
		{
			if (cmp->value < cur->value)
				rank++;
			cmp = cmp->next;
		}
		cur->indx = rank;
		cur = cur->next;
	}
}

int	complex_max_bits_for_size(int size)
{
	int	max_index;
	int	bits;

	max_index = size - 1;
	bits = 0;
	while ((max_index >> bits) != 0)
		bits++;
	return (bits);
}

void	complex_run_radix_pass(t_stack *a, t_stack *b, t_flags *flag, int bit)
{
	int	i;
	int	size;

	i = 0;
	size = a->size;
	while (i < size)
	{
		if (((a->top->indx >> bit) & 1) == 1)
			ra(a, flag);
		else
			pb(a, b, flag);
		i++;
	}
	while (b->size > 0)
		pa(a, b, flag);
}
