/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 01:48:15 by metaskin          #+#    #+#             */
/*   Updated: 2026/03/14 08:00:34 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BENCH_H
# define BENCH_H

typedef enum e_which_algo
{
	ADAPTIVE,
	SIMPLE,
	MEDIUM,
	COMPLEX
}					t_which_algo;

typedef struct s_flags
{
	t_which_algo	which_algo;
	int				bench;
	int				algo_set;
}					t_flags;

typedef struct s_bench
{
	int				enabled;
	int				total_ops;
	int				disorder;
	t_which_algo	strategy;
}				t_bench;

void				init_flags(t_flags *flag);
int					is_flag(char *arg);
int					do_flag(t_flags *flags, char *arg);
int					parse_flags(int argc, char **argv, t_flags *flags,
						int *start);

#endif
