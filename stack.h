/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 16:58:00 by metaskin          #+#    #+#             */
/*   Updated: 2026/04/17 12:54:19 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

typedef struct s_node
{
	int				value;
	int				indx;
	struct s_node	*next;
	struct s_node	*prev;
}					t_node;

typedef struct s_stack
{
	int				size;
	t_node			*top;
	t_node			*bottom;
}					t_stack;

/* stack.c */
void				create_stack(t_stack *stack);
void				clear_stack(t_stack *stack);
t_node				*node_new(int value);
void				stack_add_back(t_stack *stack, t_node *node);
void				stack_build(t_stack *stack, char **args);

#endif
