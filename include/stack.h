/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asobolev <asobolev@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 16:58:00 by metaskin          #+#    #+#             */
/*   Updated: 2026/03/24 21:34:55 by asobolev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

# include <stdlib.h>

typedef struct s_node
{
	int				value;
	int 			indx;
	struct s_node	*next;
	struct s_node	*prev;
}					t_node;

typedef struct s_stack
{
	int				size;
	t_node			*top;
	t_node          *bottom;	
}					t_stack;

/* stack.c */
void				create_stack(t_stack *stack);
void				clear_stack(t_stack *stack);
t_node				*node_new(int value);
void				stack_add_back(t_stack *stack, t_node *node);
void				stack_build(t_stack *stack, char **args);

#endif
