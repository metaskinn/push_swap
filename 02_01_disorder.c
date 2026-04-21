/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_01_disorder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 22:05:31 by metaskin          #+#    #+#             */
/*   Updated: 2026/04/16 13:52:23 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static double	get_value_at_index(t_stack head, int index)
{
	t_stack	a;
	int		cursor;

	a = head;
	cursor = 0;
	while (cursor < index)
	{
		a.top = a.top->next;
		cursor++;
	}
	return (a.top->value);
}

static double	count_inversions(t_stack head, int i, int size)
{
	double	mistakes;
	double	firstv;
	double	secondv;
	int		j;

	mistakes = 0;
	firstv = get_value_at_index(head, i);
	j = i + 1;
	while (j < size)
	{
		secondv = get_value_at_index(head, j);
		if (firstv > secondv)
			mistakes++;
		j++;
	}
	return (mistakes);
}

double	compute_disorder(t_stack head)
{
	double	mistakes;
	double	tpairs;
	int		i;
	int		size;

	size = head.size;
	mistakes = 0;
	tpairs = 0;
	i = 0;
	while (i < size)
	{
		mistakes += count_inversions(head, i, size);
		tpairs += (size - i - 1);
		i++;
	}
	if (tpairs == 0)
		return (0.0);
	return (mistakes / tpairs);
}
