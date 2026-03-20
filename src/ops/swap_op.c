/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 15:41:21 by asobolev          #+#    #+#             */
/*   Updated: 2026/03/20 19:37:41 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ops.h"
#include <unistd.h>

void	sa(t_stack *a, t_flags *flag)
{
	t_node	*first;
	t_node	*second;

	if (!a || a->size < 2)
		return ;
	// ilk iki dugumu degistir
	first = a->top;
	second = first->next;
	first->next = second->next;
	second->next = first;
	a->top = second;
	if (flag)
	{
		flag->total_ops++;
		if (flag->enabled && !flag->bench)
			write(1, "sa\n", 3);
	}
}

void	sb(t_stack *b, t_flags *flag)
{
	t_node	*first;
	t_node	*second;

	if (!b || b->size < 2)
		return ;
	// ilk iki dugumu degistir
	first = b->top;
	second = first->next;
	first->next = second->next;
	second->next = first;
	b->top = second;
	if (flag)
	{
		flag->total_ops++;
		if (flag->enabled && !flag->bench)
			write(1, "sb\n", 3);
	}
}

static int	ss_one_stack(t_stack *stack)
{
	t_node	*first;
	t_node	*second;

	if (!stack || stack->size < 2)
		return (0);
	// ss icin ayni swap mantigi
	first = stack->top;
	second = first->next;
	first->next = second->next;
	second->next = first;
	stack->top = second;
	return (1);
}

void	ss(t_stack *a, t_stack *b, t_flags *flag)
{
	int	changed_a;
	int	changed_b;

	// iki stack'i degistir, bir kez ss yaz
	changed_a = ss_one_stack(a);
	changed_b = ss_one_stack(b);
	if ((changed_a || changed_b) && flag)
	{
		flag->total_ops++;
		if (flag->enabled && !flag->bench)
			write(1, "ss\n", 3);
	}
}
