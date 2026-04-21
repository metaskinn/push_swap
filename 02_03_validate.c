/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_03_validate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 00:00:00 by metaskin          #+#    #+#             */
/*   Updated: 2026/04/21 17:03:58 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	is_positive_int(char *digits)
{
	if (ft_strlen(digits) > 10)
		return (0);
	if (ft_strlen(digits) == 10 && ft_strcmp(digits, "2147483647") > 0)
		return (0);
	return (1);
}

static int	is_negative_int(char *digits)
{
	if (ft_strlen(digits) > 10)
		return (0);
	if (ft_strlen(digits) == 10 && ft_strcmp(digits, "2147483648") > 0)
		return (0);
	return (1);
}

static int	validate_int_range(char *str)
{
	int	sign;
	int	i;

	i = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (sign == 1)
		return (is_positive_int(str + i));
	return (is_negative_int(str + i));
}

int	check_numbers(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (!is_numstr(args[i]))
			return (1);
		if (!validate_int_range(args[i]))
			return (1);
		i++;
	}
	if (has_dup(args))
		return (1);
	return (0);
}
