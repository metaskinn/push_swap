/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 08:03:20 by metaskin          #+#    #+#             */
/*   Updated: 2026/03/14 08:05:58 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "stack.h"
#include "utils.h"

void	stack_init(t_stack *stack)
{
	stack->top = NULL;
	stack->size = 0;
}

void	stack_clear(t_stack *stack)
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

static t_node	*node_new(int value)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->value = value;
	node->next = NULL;
	return (node);
}

static void	stack_add_back(t_stack *stack, t_node *node)
{
	t_node	*last;

	if (stack->top == NULL)
		stack->top = node;
	else
	{
		last = stack->top;
		while (last->next != NULL)
			last = last->next;
		last->next = node;
	}
	stack->size++;
}

void	stack_build_from_args(t_stack *stack, char **args)
{
	int		index;
	t_node	*node;

	index = 0;
	while (args[index] != NULL)
	{
		node = node_new((int)ft_atol(args[index]));
		if (node == NULL)
		{
			stack_clear(stack);
			error();
		}
		stack_add_back(stack, node);
		index++;
	}
}
