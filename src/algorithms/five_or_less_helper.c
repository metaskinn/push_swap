/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   five_or_less_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asobolev <asobolev@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 05:30:00 by asobolev          #+#    #+#             */
/*   Updated: 2026/04/15 05:51:06 by asobolev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algo.h"
#include "ops.h"

int	find_min_pos(t_stack *a)
{
	t_node	*cur;
	int		min_val;
	int		min_pos;
	int		pos;

	cur = a->top;
	min_val = cur->value;
	min_pos = 0;
	pos = 0;
	while (cur)
	{
		if (cur->value < min_val)
		{
			min_val = cur->value;
			min_pos = pos;
		}
		cur = cur->next;
		pos++;
	}
	return (min_pos);
}

void	rotate_to_min(t_stack *a, int pos, t_flags *flag)
{
	if (pos == 0)
		return ;
	if (pos <= a->size / 2)
	{
		while (pos > 0)
		{
			ra(a, flag);
			pos--;
		}
	}
	else
	{
		pos = a->size - pos;
		while (pos > 0)
		{
			rra(a, flag);
			pos--;
		}
	}
}
