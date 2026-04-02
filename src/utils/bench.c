/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 03:30:00 by metaskin          #+#    #+#             */
/*   Updated: 2026/04/02 03:07:46 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algo.h"
#include "ops.h"
#include "utils.h"

static const char	*strategy_name(t_which_algo algo)
{
	if (algo == SIMPLE)
		return ("Simple");
	if (algo == MEDIUM)
		return ("Medium");
	if (algo == COMPLEX)
		return ("Complex");
	return ("Adaptive");
}

static const char	*strategy_complexity(t_flags *flag)
{
	if (flag->which_algo == SIMPLE)
		return ("$O(n^2)$");
	if (flag->which_algo == MEDIUM)
		return ("$O(n\\sqrt{n})$");
	if (flag->which_algo == COMPLEX)
		return ("$O(n\\log n)$");
	if (flag->disorder < 0.2)
		return ("$O(n^2)$");
	if (flag->disorder < 0.5)
		return ("$O(n\\sqrt{n})$");
	return ("$O(n\\log n)$");
}

static void	print_op_counts(t_flags *flag)
{
	ft_printf_fd(2, "[bench] sa: %d sb: %d ss: %d pa: %d pb: %d\n",
		flag->op_count[OP_SA], flag->op_count[OP_SB], flag->op_count[OP_SS],
		flag->op_count[OP_PA], flag->op_count[OP_PB]);
	ft_printf_fd(2, "[bench] ra: %d rb: %d rr: %d rra: %d rrb: %d rrr: %d\n",
		flag->op_count[OP_RA], flag->op_count[OP_RB], flag->op_count[OP_RR],
		flag->op_count[OP_RRA], flag->op_count[OP_RRB], flag->op_count[OP_RRR]);
}

static void	print_disorder_percent(double disorder)
{
	int	scaled;
	int	int_part;
	int	frac_part;

	scaled = (int)(disorder * 10000.0 + 0.5);
	int_part = scaled / 100;
	frac_part = scaled % 100;
	if (frac_part < 10)
		ft_printf_fd(2, "[bench] disorder: %d.0%d%%\n", int_part, frac_part);
	else
		ft_printf_fd(2, "[bench] disorder: %d.%d%%\n", int_part, frac_part);
}

void	print_benchmark(t_program *program)
{
	print_disorder_percent(program->flag.disorder);
	ft_printf_fd(2, "[bench] strategy: %s / %s\n",
		strategy_name(program->flag.which_algo),
		strategy_complexity(&program->flag));
	ft_printf_fd(2, "[bench] total_ops: %d\n", program->flag.total_ops);
	print_op_counts(&program->flag);
}
