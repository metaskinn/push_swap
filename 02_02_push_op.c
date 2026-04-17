/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_02_push_op.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 15:40:49 by asobolev          #+#    #+#             */
/*   Updated: 2026/04/17 13:01:53 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ops.h"
#include <unistd.h>

static void	count_push_op(t_flags *flag, t_op op, char *name)
{
	if (!flag)
		return ;
	flag->total_ops++;
	flag->op_count[op]++;
	if (flag->enabled)
		write(1, name, 3);
}

static void	move_from_b_to_a(t_stack *a, t_stack *b)
{
	t_node	*node;

	node = b->top;
	b->top = node->next;
	if (b->top)
		b->top->prev = NULL;
	else
		b->bottom = NULL;
	b->size--;
	node->prev = NULL;
	node->next = a->top;
	if (a->top)
		a->top->prev = node;
	else
		a->bottom = node;
	a->top = node;
	a->size++;
}

static void	move_from_a_to_b(t_stack *a, t_stack *b)
{
	t_node	*node;

	node = a->top;
	a->top = node->next;
	if (a->top)
		a->top->prev = NULL;
	else
		a->bottom = NULL;
	a->size--;
	node->prev = NULL;
	node->next = b->top;
	if (b->top)
		b->top->prev = node;
	else
		b->bottom = node;
	b->top = node;
	b->size++;
}

void	pa(t_stack *a, t_stack *b, t_flags *flag)
{
	if (!a || !b || b->size == 0)
		return ;
	move_from_b_to_a(a, b);
	count_push_op(flag, OP_PA, "pa\n");
}

void	pb(t_stack *a, t_stack *b, t_flags *flag)
{
	if (!a || !b || a->size == 0)
		return ;
	move_from_a_to_b(a, b);
	count_push_op(flag, OP_PB, "pb\n");
}
