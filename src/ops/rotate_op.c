/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 15:41:16 by asobolev          #+#    #+#             */
/*   Updated: 2026/03/20 17:17:19 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algo.h"
#include <unistd.h>

void	ra(t_stack *a, t_flags *flag)
{
	t_node	*first;
	t_node	*last;

	if (!a || a->size < 2)
		return ;
	first = a->top;
	a->top = first->next;
	first->next = NULL;
	last = a->top;
	while (last->next)
		last = last->next;
	last->next = first;
	if (flag)
	{
		flag->total_ops++;
		if (flag->enabled && !flag->bench)
			write(1, "ra\n", 3);
	}
}

void	rb(t_stack *b, t_flags *flag)
{
	t_node	*first;
	t_node	*last;

	if (!b || b->size < 2)
		return ;
	first = b->top;
	b->top = first->next;
	first->next = NULL;
	last = b->top;
	while (last->next)
		last = last->next;
	last->next = first;
	if (flag)
	{
		flag->total_ops++;
		if (flag->enabled && !flag->bench)
			write(1, "rb\n", 3);
	}
}

static int	rr_one_stack(t_stack *stack)
{
	t_node	*first;
	t_node	*last;

	if (!stack || stack->size < 2)
		return (0);
	first = stack->top;
	stack->top = first->next;
	first->next = NULL;
	last = stack->top;
	while (last->next)
		last = last->next;
	last->next = first;
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
		if (flag->enabled && !flag->bench)
			write(1, "rr\n", 3);
	}
}
