/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   five_or_less.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asobolev <asobolev@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 04:28:48 by asobolev          #+#    #+#             */
/*   Updated: 2026/04/15 05:48:19 by asobolev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algo.h"
#include "ops.h"

void	sort_two(t_stack *a, t_flags *flag)
{
	if (a->top->value > a->top->next->value)
		sa(a, flag);
}

void	sort_three(t_stack *a, t_flags *flag)
{
	if (a->top->value > a->top->next->value
		&& a->top->next->value > a->bottom->value)
	{
		ra(a, flag);
		sa(a, flag);
	}
	else if (a->top->value > a->top->next->value
		&& a->top->next->value < a->bottom->value)
		ra(a, flag);
	else if (a->top->value < a->top->next->value
		&& a->top->value > a->bottom->value)
		rra(a, flag);
	else if (a->top->value > a->top->next->value
		&& a->top->value < a->bottom->value)
		sa(a, flag);
	else if (a->top->value < a->top->next->value
		&& a->top->next->value > a->bottom->value)
	{
		rra(a, flag);
		sa(a, flag);
	}
}

void	sort_four(t_stack *a, t_stack *b, t_flags *flag)
{
	int	pos;

	pos = find_min_pos(a);
	rotate_to_min(a, pos, flag);
	pb(a, b, flag);
	sort_three(a, flag);
	pa(a, b, flag);
}

void	sort_five(t_stack *a, t_stack *b, t_flags *flag)
{
	int	pos;

	pos = find_min_pos(a);
	rotate_to_min(a, pos, flag);
	pb(a, b, flag);
	pos = find_min_pos(a);
	rotate_to_min(a, pos, flag);
	pb(a, b, flag);
	sort_three(a, flag);
	pa(a, b, flag);
	pa(a, b, flag);
}

void	five_or_less_sort(t_stack *a, t_stack *b, t_flags *flag)
{
	if (a->size == 1)
		return ;
	else if (a->size == 2)
		sort_two(a, flag);
	else if (a->size == 3)
		sort_three(a, flag);
	else if (a->size == 4)
		sort_four(a, b, flag);
	else if (a->size == 5)
		sort_five(a, b, flag);
}
