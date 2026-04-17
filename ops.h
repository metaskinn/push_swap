/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 16:50:25 by metaskin          #+#    #+#             */
/*   Updated: 2026/04/17 12:55:22 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPS_H
# define OPS_H

# include "parser.h"
# include "stack.h"

typedef enum e_op
{
	OP_SA,
	OP_SB,
	OP_SS,
	OP_PA,
	OP_PB,
	OP_RA,
	OP_RB,
	OP_RR,
	OP_RRA,
	OP_RRB,
	OP_RRR
}		t_op;

/* swap_op.c */
void	sa(t_stack *a, t_flags *flag);
void	sb(t_stack *b, t_flags *flag);
void	ss(t_stack *a, t_stack *b, t_flags *flag);

/* push_op.c */
void	pa(t_stack *a, t_stack *b, t_flags *flag);
void	pb(t_stack *a, t_stack *b, t_flags *flag);

/* rotate_op.c */
void	ra(t_stack *a, t_flags *flag);
void	rb(t_stack *b, t_flags *flag);
void	rr(t_stack *a, t_stack *b, t_flags *flag);

/* reverse_rotate_op.c */
void	rra(t_stack *a, t_flags *flag);
void	rrb(t_stack *b, t_flags *flag);
void	rrr(t_stack *a, t_stack *b, t_flags *flag);

#endif
