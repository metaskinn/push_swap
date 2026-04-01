/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 03:30:00 by metaskin          #+#    #+#             */
/*   Updated: 2026/04/02 02:43:20 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algo.h"
#include "ops.h"
#include <stdio.h>

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
	fprintf(stderr, "[bench] sa: %d sb: %d ss: %d pa: %d pb: %d\n",
		flag->op_count[OP_SA], flag->op_count[OP_SB], flag->op_count[OP_SS],
		flag->op_count[OP_PA], flag->op_count[OP_PB]);
	fprintf(stderr, "[bench] ra: %d rb: %d rr: %d rra: %d rrb: %d rrr: %d\n",
		flag->op_count[OP_RA], flag->op_count[OP_RB], flag->op_count[OP_RR],
		flag->op_count[OP_RRA], flag->op_count[OP_RRB], flag->op_count[OP_RRR]);
}

void	print_benchmark(t_program *program)
{
	fprintf(stderr, "[bench] disorder: %.2f%%\n", program->flag.disorder
		* 100.0);
	fprintf(stderr, "[bench] strategy: %s / %s\n",
		strategy_name(program->flag.which_algo),
		strategy_complexity(&program->flag));
	fprintf(stderr, "[bench] total_ops: %d\n", program->flag.total_ops);
	print_op_counts(&program->flag);
}
