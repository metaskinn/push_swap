/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 11:45:00 by metaskin          #+#    #+#             */
/*   Updated: 2026/03/28 20:03:25 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algo.h"
#include "ops.h"

static void	assign_indices(t_stack *a)
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

static int	find_in_chunk_pos(t_stack *a, int limit)
{
	t_node	*cur;
	int		pos;

	cur = a->top;
	pos = 0;
	while (cur)
	{
		if (cur->indx <= limit)
			return (pos);
		cur = cur->next;
		pos++;
	}
	return (-1);
}

static void	rotate_a_to_chunk(t_stack *a, int limit, t_flags *flag)
{
	int	pos;
	int	r;

	pos = find_in_chunk_pos(a, limit);
	if (pos < 0)
		return ;
	if (pos <= a->size / 2)
		while (pos-- > 0)
			ra(a, flag);
	else
	{
		r = a->size - pos;
		while (r-- > 0)
			rra(a, flag);
	}
}

static void	push_chunks_to_b(t_stack *a, t_stack *b, int chunk, t_flags *flag)
{
	int	limit;

	limit = chunk - 1;
	while (a->size > 0)
	{
		rotate_a_to_chunk(a, limit, flag);
		pb(a, b, flag);
		if (b->top && b->top->indx < limit - (chunk / 2))
			rb(b, flag);
		if (b->size > limit + 1)
			limit += chunk;
	}
}

void	medium_sort(t_stack *a, t_stack *b, t_flags *flag)
{
	int	chunk;

	if (!a || !b)
		return ;
	if (a->size < 2 || compute_disorder(*a) == 0)
		return ;
	assign_indices(a);
	if (a->size <= 100)
		chunk = 15;
	else
		chunk = 32;
	push_chunks_to_b(a, b, chunk, flag);
	push_back_to_a(a, b, flag);
}
