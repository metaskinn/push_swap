/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 01:52:49 by metaskin          #+#    #+#             */
/*   Updated: 2026/03/14 04:37:24 by metaskin         ###   ########.fr       */
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

static int	set_algo_flag(t_flags *flag, t_which_algo algo)
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
		return (set_algo_flag(flag, SIMPLE));
	else if (mt_strcmp(arg, "--medium") == 0)
		return (set_algo_flag(flag, MEDIUM));
	else if (mt_strcmp(arg, "--complex") == 0)
		return (set_algo_flag(flag, COMPLEX));
	else if (mt_strcmp(arg, "--adaptive") == 0)
		return (set_algo_flag(flag, ADAPTIVE));
	else
		return (1);
	return (0);
}

int	parse_flags(int argc, char **argv, t_flags *flag, int *start)
{
	int	i;

	i = 1;
	while (i < argc && is_flag(argv[i]))
	{
		if (do_flag(flag, argv[i]) != 0)
			return (1);
		i++;
	}
	*start = i;
	return (0);
}
