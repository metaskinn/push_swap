/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 23:50:34 by metaskin          #+#    #+#             */
/*   Updated: 2026/04/21 16:44:46 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>


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
	int				total_ops;
	int				enabled;
	double			disorder;
	int				op_count[11];
}					t_flags;

typedef struct s_parse
{
	char			**args;
	int				must_free;
}					t_parse;

typedef struct s_wspace_check
{
	int				count;
	int				index;
}					t_wspace_check;

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

typedef struct s_program
{
	t_stack			a;
	t_stack			b;
	t_flags			flag;
	t_parse			parse;
}					t_program;

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
}					t_op;

/* split.c */
int					is_wspace(char c);
char				**split(char *s);
void				free_split(char **arr);

/* atol.c */
long				ft_atol(char *str);

/* parse_helpers.c */
int					has_wspace_char(char *s);
int					is_empty_token(char *s);
int					has_edge_wspace(char *s);

/* argv_build.c */
char				*join_args(char **argv, int start, int argc);
t_wspace_check		check_argv_wspace(char **argv, int start, int argc);

/* validate.c */
int					check_numbers(char **args);

/* checks.c */
void				error(void);
void				error_cleanup(t_parse *parse);
int					is_intranger_range(long num);
int					is_numstr(char *str);
int					has_dup(char **args);

/* flags.c */
void				default_flag(t_flags *flag);
int					are_flags(char *arg);
int					apply_flag(t_flags *flag, char *arg);
int					handle_flags(int argc, char **argv, t_flags *flag,
						int *start);

/* parse.c */
int					read_args(int argc, char **argv, t_flags *flag,
						t_parse *parse);

/* stack.c */
void				create_stack(t_stack *stack);
void				clear_stack(t_stack *stack);
t_node				*node_new(int value);
void				stack_add_back(t_stack *stack, t_node *node);
void				stack_build(t_stack *stack, char **args, t_parse *parse);

/* swap_op.c */
void				sa(t_stack *a, t_flags *flag);
void				sb(t_stack *b, t_flags *flag);
void				ss(t_stack *a, t_stack *b, t_flags *flag);

/* push_op.c */
void				pa(t_stack *a, t_stack *b, t_flags *flag);
void				pb(t_stack *a, t_stack *b, t_flags *flag);

/* rotate_op.c */
void				ra(t_stack *a, t_flags *flag);
void				rb(t_stack *b, t_flags *flag);
void				rr(t_stack *a, t_stack *b, t_flags *flag);

/* reverse_rotate_op.c */
void				rra(t_stack *a, t_flags *flag);
void				rrb(t_stack *b, t_flags *flag);
void				rrr(t_stack *a, t_stack *b, t_flags *flag);

/* algo.c */
double				compute_disorder(t_stack head);
void				simple_sort(t_stack *a, t_stack *b, t_flags *flag);
void				medium_sort(t_stack *a, t_stack *b, t_flags *flag);
void				complex_sort(t_stack *a, t_stack *b, t_flags *flag);
void				adaptive_sort(t_stack *a, t_stack *b, t_flags *flag);
void				run_selected_algo(t_program *program);
void				print_benchmark(t_program *program);
void				push_back_to_a(t_stack *a, t_stack *b, t_flags *flag);
int					find_max_pos(t_stack *b);
int					find_min_pos(t_stack *a);
void				complex_assign_indices(t_stack *a);
int					complex_max_bits_for_size(int size);
void				complex_run_radix_pass(t_stack *a, t_stack *b,
						t_flags *flag, int bit);
void				five_or_less_sort(t_stack *a, t_stack *b, t_flags *flag);
void				rotate_to_min(t_stack *a, int pos, t_flags *flag);
int					is_sorted_stack(t_stack *a);

/* oldfuncs.c */
void				*ft_memset(void *b, int c, size_t n);
size_t				ft_strlen(const char *s);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strdup(const char *s);
void				*ft_calloc(size_t count, size_t size);

/* newfuncs.c */
int					ft_strcmp(const char *s1, const char *s2);

/* ft_printf_fd.c */
int					ft_printf_fd(int fd, const char *format, ...);

#endif
