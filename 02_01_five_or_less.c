/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_01_five_or_less.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 04:28:48 by asobolev          #+#    #+#             */
/*   Updated: 2026/04/16 13:52:42 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_two(t_stack *a, t_flags *flag)
{
	if (a->top->value > a->top->next->value)
		sa(a, flag);
}

void	sort_three(t_stack *a, t_flags *flag)
{
	if (a->top->value < a->top->next->value
		&& a->top->next->value < a->bottom->value)
		return ;
	if (a->top->value > a->top->next->value && a->top->next->value
		< a->bottom->value && a->top->value < a->bottom->value)
		sa(a, flag);
	else if (a->top->value > a->top->next->value
		&& a->top->next->value > a->bottom->value)
	{
		sa(a, flag);
		rra(a, flag);
	}
	else if (a->top->value > a->top->next->value && a->top->next->value
		< a->bottom->value && a->top->value > a->bottom->value)
		ra(a, flag);
	else if (a->top->value < a->top->next->value && a->top->next->value
		> a->bottom->value && a->top->value < a->bottom->value)
	{
		sa(a, flag);
		ra(a, flag);
	}
	else if (a->top->value < a->top->next->value && a->top->next->value
		> a->bottom->value && a->top->value > a->bottom->value)
		rra(a, flag);
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
	if (is_sorted_stack(a))
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
