/* ************************************************************************** */
/*                                                                            */
/*                                                         :::      ::::::::  */
/*  simple.c                                             :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*  By: asobolev <asobolev@student.42istanbul.com.tr>+#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*  Created: 2026/03/25 03:13:47 by metaskin            #+#    #+#            */
/*  Updated: 2026/03/30 17:01:41 by asobolev           ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "algo.h"
#include "ops.h"

static int	find_min_index(t_stack *a)
{
	t_node	*tmp;
	int		min_value;
	int		min_index;
	int		i;

	tmp = a->top;
	min_value = tmp->value;
	min_index = 0;
	i = 0;
	while (tmp)
	{
		if (tmp->value < min_value)
		{
			min_value = tmp->value;
			min_index = i;
		}
		tmp = tmp->next;
		i++;
	}
	return (min_index);
}

static void	rotate_simple(t_stack *a, int min_index, t_flags *flag)
{
	int	r;

	if (min_index <= a->size / 2)
	{
		r = min_index;
		while (r > 0)
		{
			ra(a, flag);
			r--;
		}
	}
	else
	{
		r = a->size - min_index;
		while (r > 0)
		{
			rra(a, flag);
			r--;
		}
	}
}

void	simple_sort(t_stack *a, t_stack *b, t_flags *flag)
{
	int	min_index;
	
	if (!a || !b)
		return ;
	if (compute_disorder(*a) == 0)
		return ;
	while (a->size > 0)
	{	
		if (compute_disorder(*a) == 0)
			break; // cod erken  şekilde  sıralanırsa diye minik optimizasyon ;))
		min_index = find_min_index(a);
		rotate_simple(a, min_index, flag);
		pb(a, b, flag);
	}
	while (b->size > 0)
		pa(a, b, flag);
}
