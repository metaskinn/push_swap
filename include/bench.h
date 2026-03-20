/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 01:48:15 by metaskin          #+#    #+#             */
/*   Updated: 2026/03/20 15:42:08 by metaskin         ###   ########.fr       */
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
	int				algo_did;
	int				total_ops;
	int				enabled;
	int				disorder;
}					t_flags;

void				default_flag(t_flags *flag);
int					are_flags(char *arg);
int					apply_flag(t_flags *flag, char *arg);
int					handle_flags(int argc, char **argv, t_flags *flag,
						int *start);

#endif
