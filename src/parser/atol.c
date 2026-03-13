/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atol.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asobolev <asobolev@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 22:30:42 by asobolev          #+#    #+#             */
/*   Updated: 2026/03/14 00:08:32 by asobolev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

long	ft_atol(char *str)
{
	long	result;
	int		sign;
	int		idx;

	result = 0;
	sign = 1;
	idx = 0;
	if (!str)
		return (error());
	while (white_space(str[idx]))
		idx++;
	if (str[idx] == '-' || str[idx] == '+')
	{
		if (str[idx] == '-')
			sign = -1;
		idx++;
	}
	if (str[idx] < '0' || str[idx] > '9')
		return (error());
	while (str[idx] >= '0' && str[idx] <= '9')
	{
		result = result * 10 + (str[idx] - '0');
		if ((result * sign) > 2147483647 || (result * sign) < -2147483648)
			return (error());
		idx++;
	}
	while (white_space(str[idx]))
		idx++;
	if (str[idx] != '\0')
		return (error());
	return (result * sign);
}
