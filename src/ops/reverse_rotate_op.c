/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate_op.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 15:41:08 by asobolev          #+#    #+#             */
/*   Updated: 2026/03/25 07:48:07 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ops.h"

void	rra(t_stack *a, t_flags *flag)
{
	t_node	*prev;
	t_node	*last;

	if (!a || a->size < 2)
		return ;
	// son dugum ve oncesini bul
	last = a->bottom;
	prev = last->prev;
	prev->next = NULL;
	a->bottom = prev;
	// sonu basa al
	last->prev = NULL;
	last->next = a->top;
	a->top->prev = last;
	a->top = last;
	if (flag)
	{
		flag->total_ops++;
		if (flag->enabled && !flag->bench)
			write(1, "rra\n", 4);
	}
}

void	rrb(t_stack *b, t_flags *flag)
{
	t_node	*prev;
	t_node	*last;

	if (!b || b->size < 2)
		return ;
	// son dugum ve oncesini bul
	last = b->bottom;
	prev = last->prev;
	prev->next = NULL;
	b->bottom = prev;
	// sonu basa al
	last->prev = NULL;
	last->next = b->top;
	b->top->prev = last;
	b->top = last;
	if (flag)
	{
		flag->total_ops++;
		if (flag->enabled && !flag->bench)
			write(1, "rrb\n", 4);
	}
}

static int	rrr_one_stack(t_stack *stack)
{
	t_node	*prev;
	t_node	*last;

	if (!stack || stack->size < 2)
		return (0);
	// rrr icin ayni reverse rotate mantigi
	last = stack->bottom;
	prev = last->prev;
	prev->next = NULL;
	stack->bottom = prev;
	last->prev = NULL;
	last->next = stack->top;
	stack->top->prev = last;
	stack->top = last;
	return (1);
}

void	rrr(t_stack *a, t_stack *b, t_flags *flag)
{
	int	changed_a;
	int	changed_b;

	// iki stack'i ters cevir, bir kez rrr yaz
	changed_a = rrr_one_stack(a);
	changed_b = rrr_one_stack(b);
	if ((changed_a || changed_b) && flag)
	{
		flag->total_ops++;
		if (flag->enabled && !flag->bench)
			write(1, "rrr\n", 4);
	}
}
