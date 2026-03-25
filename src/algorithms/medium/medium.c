/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 11:45:00 by metaskin          #+#    #+#             */
/*   Updated: 2026/03/25 07:28:25 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algo.h"

void	medium_sort(t_stack *a, t_stack *b, t_flags *flag)
{
	if (!a || !b)
		return ;
	simple_sort(a, b, flag);
}
