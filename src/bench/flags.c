/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 01:52:49 by metaskin          #+#    #+#             */
/*   Updated: 2026/03/14 05:52:47 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bench.h"
#include "utils.h"

void	init_flags(t_flags *flag)
{
	flag->which_algo = ADAPTIVE;
	flag->bench = 0;
	flag->algo_set = 0;
}

int	is_flag(char *arg)
{
	if (mt_strcmp(arg, "--bench") == 0)
		return (1);
	else if (mt_strcmp(arg, "--simple") == 0)
		return (1);
	else if (mt_strcmp(arg, "--medium") == 0)
		return (1);
	else if (mt_strcmp(arg, "--complex") == 0)
		return (1);
	else if (mt_strcmp(arg, "--adaptive") == 0)
		return (1);
	return (0);
}

static int	algo_set(t_flags *flag, t_which_algo algo)
{
	if (flag->algo_set)
		return (1);
	flag->which_algo = algo;
	flag->algo_set = 1;
	return (0);
}

int	do_flag(t_flags *flag, char *arg)
{
	if (mt_strcmp(arg, "--bench") == 0)
		flag->bench = 1;
	else if (mt_strcmp(arg, "--simple") == 0)
		return (algo_set(flag, SIMPLE));
	else if (mt_strcmp(arg, "--medium") == 0)
		return (algo_set(flag, MEDIUM));
	else if (mt_strcmp(arg, "--complex") == 0)
		return (algo_set(flag, COMPLEX));
	else if (mt_strcmp(arg, "--adaptive") == 0)
		return (algo_set(flag, ADAPTIVE));
	else
		return (1);
	return (0);
}

int	parse_flags(int argc, char **argv, t_flags *flag, int *start)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_flag(argv[i]))
			break ;
		if (do_flag(flag, argv[i]) != 0)
			return (1);
		i++;
	}
	*start = i;
	return (0);
}
