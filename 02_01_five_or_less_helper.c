/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_01_five_or_less_helper.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 05:30:00 by asobolev          #+#    #+#             */
/*   Updated: 2026/04/16 13:52:32 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algo.h"
#include "ops.h"

int	is_sorted_stack(t_stack *a)
{
	t_node	*cur;

	cur = a->top;
	while (cur && cur->next)
	{
		if (cur->value > cur->next->value)
			return (0);
		cur = cur->next;
	}
	return (1);
}

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
