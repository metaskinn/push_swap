/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 15:41:16 by asobolev          #+#    #+#             */
/*   Updated: 2026/03/25 07:48:05 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ops.h"

void	ra(t_stack *a, t_flags *flag)
{
	t_node	*first;

	if (!a || a->size < 2)
		return ;
	// ustteki dugumu al
	first = a->top;
	a->top = first->next;
	a->top->prev = NULL;
	first->next = NULL;
	first->prev = a->bottom;
	// sona ekle
	a->bottom->next = first;
	a->bottom = first;
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

	if (!b || b->size < 2)
		return ;
	// ustteki dugumu al
	first = b->top;
	b->top = first->next;
	b->top->prev = NULL;
	first->next = NULL;
	first->prev = b->bottom;
	// sona ekle
	b->bottom->next = first;
	b->bottom = first;
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

	if (!stack || stack->size < 2)
		return (0);
	// rr icin ayni rotate mantigi
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

	// iki stack'i cevir, bir kez rr yaz
	changed_a = rr_one_stack(a);
	changed_b = rr_one_stack(b);
	if ((changed_a || changed_b) && flag)
	{
		flag->total_ops++;
		if (flag->enabled && !flag->bench)
			write(1, "rr\n", 3);
	}
}
