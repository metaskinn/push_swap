/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 15:40:49 by asobolev          #+#    #+#             */
/*   Updated: 2026/03/20 17:13:09 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algo.h"
#include <unistd.h>

void	pa(t_stack *a, t_stack *b, t_flags *flag)
{
	t_node	*node;

	if (!a || !b || b->size == 0)
		return ;
	node = b->top;
	b->top = node->next;
	b->size--;
	node->next = a->top;
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
	a->size--;
	node->next = b->top;
	b->top = node;
	b->size++;
	if (flag)
	{
		flag->total_ops++;
		if (flag->enabled && !flag->bench)
			write(1, "pb\n", 3);
	}
}
