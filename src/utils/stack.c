/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 08:03:20 by metaskin          #+#    #+#             */
/*   Updated: 2026/03/20 16:46:38 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"
#include "parser.h"
#include "utils.h"

void	create_stack(t_stack *stack)
{
	stack->top = NULL;
	stack->size = 0;
}

void	clear_stack(t_stack *stack)
{
	t_node	*next;

	while (stack->top != NULL)
	{
		next = stack->top->next;
		free(stack->top);
		stack->top = next;
	}
	stack->size = 0;
}

t_node	*node_new(int value)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->value = value;
	node->next = NULL;
	return (node);
}

void	stack_add_back(t_stack *stack, t_node *node)
{
	t_node	*last;

	if (!stack->top)
		stack->top = node;
	else
	{
		last = stack->top;
		while (last->next)
			last = last->next;
		last->next = node;
	}
	stack->size += 1;
}

void	stack_build(t_stack *stack, char **args)
{
	int		index;
	t_node	*node;

	index = 0;
	while (args[index] != NULL)
	{
		node = node_new((int)ft_atol(args[index]));
		if (node == NULL)
		{
			clear_stack(stack);
			error();
		}
		stack_add_back(stack, node);
		index++;
	}
}
