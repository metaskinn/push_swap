/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_01_adaptive.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 02:35:53 by metaskin          #+#    #+#             */
/*   Updated: 2026/04/16 13:52:02 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	adaptive_sort(t_stack *a, t_stack *b, t_flags *flag)
{
	double	disorder;

	if (!a || !b)
		return ;
	if (a->size < 2)
		return ;
	if (flag && flag->disorder >= 0.0)
		disorder = flag->disorder;
	else
		disorder = compute_disorder(*a);
	if (a->size <= 5)
		five_or_less_sort(a, b, flag);
	else if (disorder < 0.2)
		simple_sort(a, b, flag);
	else if (disorder < 0.5)
		medium_sort(a, b, flag);
	else
		complex_sort(a, b, flag);
}
