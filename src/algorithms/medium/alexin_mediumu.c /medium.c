/* ************************************************************************** */
/*                                                                            */
/*                                                         :::      ::::::::  */
/*  medium.c                                             :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*  By: asobolev <asobolev@student.42istanbul.com.tr>+#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*  Created: 2026/03/31 22:16:42 by asobolev            #+#    #+#            */
/*  Updated: 2026/04/01 20:24:25 by asobolev           ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "algo.h"
#include "ops.h"

static void stack_swap(t_node *first, t_node *second)
{
	int tmp;
	
	tmp = first->value;
	first->value = second->value;
	second->value = tmp;
}
// main_stack'e index atama
static void selection_sort(t_stack *copied_stack)
{
	t_node *j;
	t_node *i;
	t_node *min;
	
	i = copied_stack->top;
	
	while (i && i->next)
	{
		min = i;
		j = i->next;
		while (j)
		{
    		if (j->value < min->value)
        	min = j;
   			j = j->next;
		}
		if (min != i)
            node_swap(i, min);
		i = i->next;
	}
}

static void index (t_stack *copied_stack, t_stack *a)
{
	t_node *tmp_a;
	t_node *tmp_copied_stack;
	int index ;

	index = 0;
	tmp_copied_stack = copied_stack->top;
	while (tmp_copied_stack)
	{
		tmp_a = a->top;
		while (tmp_a)
		{
			if (tmp_copied_stack->value == tmp_a->value)
			{
				tmp_a->indx = index;
				index++;
				break;
			}
			tmp_a = tmp_a->next;
		}
		tmp_copied_stack = tmp_copied_stack->next;
	}
}

static int chunk_numberr(t_stack *a)
{
    int chunk_number;
    int stack_size;

    stack_size = a->size;

	if (stack_size >= 3000)
		chunk_number = 30;
	else if (stack_size >= 1000)
        chunk_number = 20;
    else if (stack_size >= 500)
        chunk_number = 10;
    else if (stack_size >= 100)
        chunk_number = 5;
    else if (stack_size >= 20)
        chunk_number = 3;
    else if (stack_size >= 10)
        chunk_number = 2;
    else if (stack_size >= 5)
        chunk_number = 1;
    else
        chunk_number = 1; 
    return chunk_number;
}

void chunk (t_stack *a, t_stack *b)

{	
	int i;
	int chunk_number;
	int chunk_size;

	chunk_number = chunk_numberr(a);
	i = 0;
	chunk_size = a->size / chunk_number ;

	if (compute_disorder(*a) == 0) 
		return ;
	if (!a ||!b)
		return;
	
	while (chunk_sizee != i) 
	{
		if (a->top->indx >= chunk_size)
		{
			pb;
		}
		if 
	}

	
	
	
}