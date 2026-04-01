/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 15:41:21 by asobolev          #+#    #+#             */
/*   Updated: 2026/04/02 02:39:26 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ops.h"

void	sa(t_stack *a, t_flags *flag)
{
	t_node	*first;
	t_node	*second;

	if (!a || a->size < 2)
		return ;
	first = a->top;
	second = first->next;
	first->next = second->next;
	if (first->next)
		first->next->prev = first;
	else
		a->bottom = first;
	first->prev = second;
	second->prev = NULL;
	second->next = first;
	a->top = second;
	if (flag)
	{
		flag->total_ops++;
		flag->op_count[OP_SA]++;
		if (flag->enabled)
			write(1, "sa\n", 3);
	}
}

void	sb(t_stack *b, t_flags *flag)
{
	t_node	*first;
	t_node	*second;

	if (!b || b->size < 2)
		return ;
	first = b->top;
	second = first->next;
	first->next = second->next;
	if (first->next)
		first->next->prev = first;
	else
		b->bottom = first;
	first->prev = second;
	second->prev = NULL;
	second->next = first;
	b->top = second;
	if (flag)
	{
		flag->total_ops++;
		flag->op_count[OP_SB]++;
		if (flag->enabled)
			write(1, "sb\n", 3);
	}
}

static int	ss_one_stack(t_stack *stack)
{
	t_node	*first;
	t_node	*second;

	if (!stack || stack->size < 2)
		return (0);
	first = stack->top;
	second = first->next;
	first->next = second->next;
	if (first->next)
		first->next->prev = first;
	else
		stack->bottom = first;
	first->prev = second;
	second->prev = NULL;
	second->next = first;
	stack->top = second;
	return (1);
}

void	ss(t_stack *a, t_stack *b, t_flags *flag)
{
	int	changed_a;
	int	changed_b;

	changed_a = ss_one_stack(a);
	changed_b = ss_one_stack(b);
	if ((changed_a || changed_b) && flag)
	{
		flag->total_ops++;
		flag->op_count[OP_SS]++;
		if (flag->enabled)
			write(1, "ss\n", 3);
	}
}
