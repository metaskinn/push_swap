/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asobolev <asobolev@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:22:26 by metaskin          #+#    #+#             */
/*   Updated: 2026/03/17 15:05:26 by asobolev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	char	**splited;
	int i;
	int atoled;
	
	i = 0;
	
	if (argc == 2)
		splited = split(argv[1]);
	else
		*splited = argv[i];	
	while (splited[i] != NULL)
	{
		is_number(splited[i]);
		atoled = is_intrager_range(ft_atol(splited[i]));
		i++;
	}
	has_dup(ft_atol(splited));
	return (0);
}
