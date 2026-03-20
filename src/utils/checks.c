/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 19:42:04 by asobolev          #+#    #+#             */
/*   Updated: 2026/03/20 20:32:34 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parser.h"
# include "utils.h"

int	error(void)
{
	write(2, "Error\n", 6);
	exit(1);
}

int	is_intranger_range(long num)
{
	if (num >= -2147483648 && num <= 2147483647)
		return (1);
	return (0);
}

int	is_numstr(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	has_dup(char **args)
{
	int		i;
	int		j;
	long	a;
	long	b;

	i = 0;
	// push_swap icin O(n^2) yeterli
	while (args[i])
	{
		a = ft_atol(args[i]);
		j = i + 1;
		while (args[j])
		{
			b = ft_atol(args[j]);
			if (a == b)
				error();
			j++;
		}
		i++;
	}
	return (0);
}
