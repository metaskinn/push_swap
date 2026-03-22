#include "push_swap.h"

int	main(int argc, char **argv)
{
	char	**splited;
	int i;
	int j;
	long atoled;
	
	i = 0;
	j = 

	if (argc == 2)
		splited = split(argv[1]);
	else
		splited = argv + 1;	
	while (splited[i] != NULL)
	{
    is_numstr(splited[i]);
    atoled = ft_atol(splited[i]);
    is_intranger_range(atoled);
    i++;
	}
	has_dup(splited);
	return (0);
	


#include "parser.h"
#include "stack.h"
#include "utils.h"

t_node *make_a_node(void)
{
	t_node node;
	node = malloc(sizeof(node));
	if !(node)
		return NULL;
	node.value = 0;
	node.indx = 0;
	node.next = NULL;
	node.prev = NULL;
	return (node);
}

t_stack *make_a_stack(void)
{
	t_stack *stack;
	stack = malloc(sizeof(stack));
	if (!stack)
		return (NULL);
	stack.size = 0;
	stack.top = NULL;
	stack.bottom = NULL;
	return (stack);
}

void add_back(t_stack *stack,t_node *node)
{
	if (!stack) || (!node);
	
	if (stack->size == 0)
	{
		stack->top = node;
		stack->bottom = node;
	}
	else
	{
		stack->bottom->next = node;
		node->prev = stack->bottom;
		stack->bottom = node;
	}
	stack->size++;
}

void print_staack(t_stack stack,)
{
	t_node tmp;
	tmp = stack->top;
	while (tmp)
	{
		printf("%d\n",tmp->value);
		tmp = tmp->next;
	}
}
}

void	pb(t_stack *a, t_stack *b)
{
	t_node	*tmp;

	if (!a || a->size == 0)
		return ;

	tmp = a->top;
	a->top = tmp->next;
	if (a->top)
		a->top->prev = NULL;

	tmp->next = b->top;
	if (b->top)
		b->top->prev = tmp;

	tmp->prev = NULL;
	b->top = tmp;

	a->size--;
	b->size++;
}

void	pb(t_stack *a, t_stack *b)
{
	t_node	*tmp;

	if (!a || a->size == 0)
		return ;

	tmp = a->top;
	a->top = tmp->next;
	if (a->top)
		a->top->prev = NULL;

	tmp->next = b->top;
	if (b->top)
		b->top->prev = tmp;

	tmp->prev = NULL;
	b->top = tmp;

	a->size--;
	b->size++;
}

void	ra(t_stack *a)
{
	t_node	*first;

	if (!a || a->size < 2)
		return ;

	first = a->top;
	a->top = first->next;
	a->top->prev = NULL;

	a->bottom->next = first;
	first->prev = a->bottom;
	first->next = NULL;

	a->bottom = first;
}

void	sa(t_stack *a)
{
	write(1, "sa\n", 3);
}