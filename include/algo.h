/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 18:22:57 by metaskin          #+#    #+#             */
/*   Updated: 2026/03/20 16:51:17 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGO_H
# define ALGO_H

# include "parser.h"
# include "stack.h"

void	sa(t_stack *a, t_flags *flag);
void	sb(t_stack *b, t_flags *flag);
void	ss(t_stack *a, t_stack *b, t_flags *flag);

void	pa(t_stack *a, t_stack *b, t_flags *flag);
void	pb(t_stack *a, t_stack *b, t_flags *flag);

void	ra(t_stack *a, t_flags *flag);
void	rb(t_stack *b, t_flags *flag);
void	rr(t_stack *a, t_stack *b, t_flags *flag);

void	rra(t_stack *a, t_flags *flag);
void	rrb(t_stack *b, t_flags *flag);
void	rrr(t_stack *a, t_stack *b, t_flags *flag);

#endif
