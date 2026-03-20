/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 01:52:49 by metaskin          #+#    #+#             */
/*   Updated: 2026/03/20 18:24:09 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

void	default_flag(t_flags *flag)
{
	flag->which_algo = ADAPTIVE;
	flag->bench = 0;
	flag->algo_did = 0;
	flag->total_ops = 0;
	flag->enabled = 1;
	flag->disorder = 0;
}

int	are_flags(char *arg)
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

static int	pre_algo(t_flags *flag, t_which_algo algo)
{
	if (flag->algo_did) // so it never re erter if already algo is did
		return (1);
	flag->which_algo = algo;
	flag->algo_did = 1;
	return (0);
}

int	apply_flag(t_flags *flag, char *arg)
{
	// after a selector already sorted dont use extra flags like that
	if (flag->algo_did && (mt_strcmp(arg, "--bench") == 0 || mt_strcmp(arg,
				"--simple") == 0 || mt_strcmp(arg, "--medium") == 0
			|| mt_strcmp(arg, "--complex") == 0 || mt_strcmp(arg,
				"--adaptive") == 0))
		return (1); // if algo ar did flag is bench --like extra
	else if (mt_strcmp(arg, "--bench") == 0)
		flag->bench = 1; // if bench is didnot
	else if (mt_strcmp(arg, "--simple") == 0)
		return (pre_algo(flag, SIMPLE));
	else if (mt_strcmp(arg, "--medium") == 0)
		return (pre_algo(flag, MEDIUM));
	else if (mt_strcmp(arg, "--complex") == 0)
		return (pre_algo(flag, COMPLEX));
	else if (mt_strcmp(arg, "--adaptive") == 0)
		return (pre_algo(flag, ADAPTIVE));
	else
		return (1);
	return (0);
}

int	handle_flags(int argc, char **argv, t_flags *flag, int *start)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!are_flags(argv[i]))
			break ;// flag is befr num so if non flag break start num
		if (apply_flag(flag, argv[i]))
			return (1);// if flag wrong
		i++;
	}
	*start = i; // start num index
	return (0);
}
