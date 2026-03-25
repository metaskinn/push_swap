/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 18:22:57 by metaskin          #+#    #+#             */
/*   Updated: 2026/03/25 05:54:42 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGO_H
# define ALGO_H

# include "parser.h"
# include "stack.h"

typedef struct s_algo
{
	
}		t_algo;

double	compute_disorder(t_stack head);
void	simple_sort(t_stack *a, t_stack *b, t_flags *flag);
void	medium_sort(t_stack *a, t_stack *b, t_flags *flag);
void	complex_sort(t_stack *a, t_stack *b, t_flags *flag);

#endif
