/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atol.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asobolev <asobolev@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 22:30:42 by asobolev          #+#    #+#             */
/*   Updated: 2026/03/13 12:54:35 by asobolev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int error(void)
{
	write(2, "error\n", 6);
	exit(1);
}

long	ft_atol(char *str)
{
	long	result;
	int		sign;
	int		idx;

	result = 0;
	sign = 1;
	idx = 0;
	while ((str[idx] >= 9 && str[idx] <= 13) || str[idx] == 32)
		idx++;
	if (str[idx] == '-' || str[idx] == '+')
	{
		if (str[idx] == '-')
			sign = -1;
		idx++;
	}
	while (str[idx] >= '0' && str[idx] <= '9')
	{
		result = result * 10 + (str[idx] - '0');
		if(result > 2147483647 || result < -2147483648)
			return (error());

		idx++;
	}
	return (result * sign);
}
