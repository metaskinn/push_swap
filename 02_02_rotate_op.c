/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_02_rotate_op.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 15:41:16 by asobolev          #+#    #+#             */
/*   Updated: 2026/04/16 13:53:23 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ops.h"

void	ra(t_stack *a, t_flags *flag)
{
	t_node	*first;

	if (!a || a->size < 2)
		return ;
	first = a->top;
	a->top = first->next;
	a->top->prev = NULL;
	first->next = NULL;
	first->prev = a->bottom;
	a->bottom->next = first;
	a->bottom = first;
	if (flag)
	{
		flag->total_ops++;
		flag->op_count[OP_RA]++;
		if (flag->enabled)
			write(1, "ra\n", 3);
	}
}

void	rb(t_stack *b, t_flags *flag)
{
	t_node	*first;

	if (!b || b->size < 2)
		return ;
	first = b->top;
	b->top = first->next;
	b->top->prev = NULL;
	first->next = NULL;
	first->prev = b->bottom;
	b->bottom->next = first;
	b->bottom = first;
	if (flag)
	{
		flag->total_ops++;
		flag->op_count[OP_RB]++;
		if (flag->enabled)
			write(1, "rb\n", 3);
	}
}

static int	rr_one_stack(t_stack *stack)
{
	t_node	*first;

	if (!stack || stack->size < 2)
		return (0);
	first = stack->top;
	stack->top = first->next;
	stack->top->prev = NULL;
	first->next = NULL;
	first->prev = stack->bottom;
	stack->bottom->next = first;
	stack->bottom = first;
	return (1);
}

void	rr(t_stack *a, t_stack *b, t_flags *flag)
{
	int	changed_a;
	int	changed_b;

	changed_a = rr_one_stack(a);
	changed_b = rr_one_stack(b);
	if ((changed_a || changed_b) && flag)
	{
		flag->total_ops++;
		flag->op_count[OP_RR]++;
		if (flag->enabled)
			write(1, "rr\n", 3);
	}
}
