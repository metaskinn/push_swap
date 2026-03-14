/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atol.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 22:30:42 by asobolev          #+#    #+#             */
/*   Updated: 2026/03/14 06:40:54 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

static long	parse_number(char *str, int *i, int sign)
{
	long	result;

	result = 0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		result = result * 10 + (str[*i] - '0');
		if ((result * sign) > 2147483647 || (result * sign) < -2147483648)
			return (error());
		(*i)++;
	}
	return (result);
}

long	ft_atol(char *str)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	if (!str)
		return (error());
	while (is_wspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (str[i] < '0' || str[i] > '9')
		return (error());
	result = parse_number(str, &i, sign);
	while (is_wspace(str[i]))
		i++;
	if (str[i] != '\0')
		return (error());
	return (result * sign);
}
