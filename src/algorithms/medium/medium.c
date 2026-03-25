/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 11:45:00 by metaskin          #+#    #+#             */
/*   Updated: 2026/03/25 07:48:31 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algo.h"

static void	assign_indices(t_stack *a)
{
	t_node	*cur;
	t_node	*cmp;
	int		rank;

	cur = a->top;
	while (cur)
	{
		rank = 0;
		cmp = a->top;
		while (cmp)
		{
			if (cmp->value < cur->value)
				rank++;
			cmp = cmp->next;
		}
		cur->indx = rank;
		cur = cur->next;
	}
}

void	medium_sort(t_stack *a, t_stack *b, t_flags *flag)
{
	if (!a || !b)
		return ;
	assign_indices(a);
	simple_sort(a, b, flag);
}
