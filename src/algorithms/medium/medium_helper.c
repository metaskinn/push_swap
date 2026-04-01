/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asobolev <asobolev@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 20:02:51 by metaskin          #+#    #+#             */
/*   Updated: 2026/03/30 06:07:42 by asobolev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ops.h"

int	find_max_pos(t_stack *b)
{
	t_node	*cur;
	int		max;
	int		max_pos;
	int		pos;

	cur = b->top;
	max = cur->indx;
	max_pos = 0;
	pos = 0;
	while (cur)
	{
		if (cur->indx > max)
		{
			max = cur->indx;
			max_pos = pos;
		}
		cur = cur->next;
		pos++;
	}
	return (max_pos);
}

void	push_back_to_a(t_stack *a, t_stack *b, t_flags *flag)
{
	int	pos;
	int	r;

	while (b->size > 0)
	{
		pos = find_max_pos(b);
		if (pos <= b->size / 2)
			while (pos-- > 0)
				rb(b, flag);
		else
		{
			r = b->size - pos;
			while (r-- > 0)
				rrb(b, flag);
		}
		pa(a, b, flag);
	}
}
