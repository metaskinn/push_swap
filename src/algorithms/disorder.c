/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disorder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 22:05:31 by metaskin          #+#    #+#             */
/*   Updated: 2026/03/25 01:19:47 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

double	compute_disorder(t_stack head)
{
	double	mistakes;
	double	tpairs;
	double	i;
	double	j;
	int		size;
	double	firstv;
	double	secondv;
	t_stack	a;
	double	cursor;

	size = head.size;
	mistakes = 0;
	tpairs = 0;
	i = 0;
	while (i < size)
	{
		cursor = 0;
		a = head;
		while (cursor < i)
		{
			a.top = a.top->next;
			cursor++;
		}
		firstv = a.top->value;
		j = i + 1;
		while (j < size)
		{
			a = head;
			cursor = 0;
			while (cursor < j)
			{
				a.top = a.top->next;
				cursor++;
			}
			secondv = a.top->value;
			if (firstv > secondv)
				mistakes++;
			j++;
			tpairs++;
		}
		i++;
	}
	return (mistakes / tpairs);
}
