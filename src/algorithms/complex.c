/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 07:31:00 by metaskin          #+#    #+#             */
/*   Updated: 2026/04/02 01:53:26 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algo.h"

void	complex_sort(t_stack *a, t_stack *b, t_flags *flag)
{
	if (!a || !b)
		return ;
	simple_sort(a, b, flag);
}
