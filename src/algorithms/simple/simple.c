/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 03:13:47 by metaskin          #+#    #+#             */
/*   Updated: 2026/03/25 06:01:46 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algo.h"
#include "ops.h"
#include <stdlib.h>

void	simple_sort(t_stack *a, t_stack *b, t_flags *flag)
{
	t_node	*tmp;
	int		min_value;
	int		min_index;
	int		i;
	int		r;

	if (compute_disorder(*a) == 0 || !a || !b || a->size > 2)
		return ;
	while (a->size > 0)
	{
		tmp = a->top;
		min_value = tmp->value;
		min_index = 0;
		i = 0;
		while (tmp)
		{
			if (tmp->value < min_value)
			{
				min_value = tmp->value;
				min_index = i;
			}
			tmp = tmp->next;
			i++;
		} // min_index buldum
		r = min_index;
		while (r > 0)
		{
			ra(a, flag);
			r--;
		}
		pb(a, b, flag);
	}
	while (b->size > 0)
		pa(a, b, flag);
}
