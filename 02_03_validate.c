/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_03_validate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 00:00:00 by metaskin          #+#    #+#             */
/*   Updated: 2026/04/16 13:54:35 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

void	check_numbers(char **args)
{
	int		i;
	long	number;

	i = 0;
	while (args[i])
	{
		if (!is_numstr(args[i]))
			error();
		number = ft_atol(args[i]);
		if (!is_intranger_range(number))
			error();
		i++;
	}
	if (has_dup(args))
		error();
}
