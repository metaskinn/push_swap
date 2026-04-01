/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 15:40:49 by asobolev          #+#    #+#             */
/*   Updated: 2026/04/02 01:53:43 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ops.h"

void	pa(t_stack *a, t_stack *b, t_flags *flag)
{
	t_node	*node;

	if (!a || !b || b->size == 0)
		return ;
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
	if (flag)
	{
		flag->total_ops++;
		if (flag->enabled && !flag->bench)
			write(1, "pa\n", 3);
	}
}

void	pb(t_stack *a, t_stack *b, t_flags *flag)
{
	t_node	*node;

	if (!a || !b || a->size == 0)
		return ;
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
	if (flag)
	{
		flag->total_ops++;
		if (flag->enabled && !flag->bench)
			write(1, "pb\n", 3);
	}
}
