/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 01:48:15 by metaskin          #+#    #+#             */
/*   Updated: 2026/03/17 17:11:02 by metaskin         ###   ########.fr       */
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
}					t_flags;

int	are_flags(char *arg);
int	apply_flag(t_flags *flag, char *arg);

#endif
