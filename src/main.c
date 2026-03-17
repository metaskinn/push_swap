/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:22:26 by metaskin          #+#    #+#             */
/*   Updated: 2026/03/17 18:26:35 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// int	main(int argc, char **argv)
// {
// 	char	**splited;
// 	int i;
// 	long atoled;

// 	i = 0;

// 	if (argc == 2)
// 		splited = split(argv[1]);
// 	else
// 		splited = argv + 1;

// 	while (splited[i] != NULL)
// {
//     is_numstr(splited[i]);
//     atoled = ft_atol(splited[i]);
//     is_intranger_range(atoled);
//     i++;
// }
// 	has_dup(splited);
// 	return (0);
// }

int main(int argc, char **argv)
{
	t_program	program;

	if (!read_args(argc, argv, &program.flag))
		error();
	program.args = argv;

	return (0);
}
