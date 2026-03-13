/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:22:26 by metaskin          #+#    #+#             */
/*   Updated: 2026/03/14 00:19:16 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	int		i;
	int		atol;
	char	*strng;
	char	**splitend;

	if (argc < 2)
		return (0);
	i = 0;
	strng = "   21 44+ 55 86";
	splitend = split(strng);
	while (splitend[i] != NULL)
	{
		if (is_int(atol) == 0)
			error();
		i++;
	}
	return (0);
}
