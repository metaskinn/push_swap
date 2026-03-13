/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 01:52:49 by metaskin          #+#    #+#             */
/*   Updated: 2026/03/14 02:31:09 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

int	apply_flag(t_flags *flag, char *arg)
{
	if (mt_strcmp(arg, "--bench") == 0)
		flag->bench = 1;
	else if (mt_strcmp(arg, "--simple") == 0)
	{
		if (flag->algo_set)
			return (1);
		flag->which_algo = SIMPLE;
		flag->algo_set = 1;
	}
	else if (mt_strcmp(arg, "--medium") == 0)
	{
		if (flag->algo_set)
			return (1);
		flag->which_algo = MEDIUM;
		flag->algo_set = 1;
	}
	else if (mt_strcmp(arg, "--complex") == 0)
	{
		if (flag->algo_set)
			return (1);
		flag->which_algo = COMPLEX;
		flag->algo_set = 1;
	}
	else if (mt_strcmp(arg, "--adaptive") == 0)
	{
		if (flag->algo_set)
			return (1);
		flag->which_algo = ADAPTIVE;
		flag->algo_set = 1;
	}
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
		if (apply_flag(flag, argv[i]) != 0)
			return (1);
		i++;
	}
	*start = i;
	return (0);
}
