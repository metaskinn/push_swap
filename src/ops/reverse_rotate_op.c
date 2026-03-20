/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate_op.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 15:41:08 by asobolev          #+#    #+#             */
/*   Updated: 2026/03/20 19:37:36 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ops.h"
#include <unistd.h>

void	rra(t_stack *a, t_flags *flag)
{
	t_node	*prev;
	t_node	*last;

	if (!a || a->size < 2)
		return ;
	prev = NULL;
	// son dugum ve oncesini bul
	last = a->top;
	while (last->next)
	{
		prev = last;
		last = last->next;
	}
	prev->next = NULL;
	// sonu basa al
	last->next = a->top;
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
	prev = NULL;
	// son dugum ve oncesini bul
	last = b->top;
	while (last->next)
	{
		prev = last;
		last = last->next;
	}
	prev->next = NULL;
	// sonu basa al
	last->next = b->top;
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
	prev = NULL;
	// rrr icin ayni reverse rotate mantigi
	last = stack->top;
	while (last->next)
	{
		prev = last;
		last = last->next;
	}
	prev->next = NULL;
	last->next = stack->top;
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
