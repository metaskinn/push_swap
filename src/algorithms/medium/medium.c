/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 11:45:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/25 07:02:23 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algo.h"
#include "ops.h"


void	medium_sort(t_stack *a, t_stack *b, t_flags *flag)
{
	t_node	*tmp;
	int		i;


	if (!a || !b)
		return ;
	if (compute_disorder(*a) == 0)
		return ;


}
