/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 17:05:00 by metaskin          #+#    #+#             */
/*   Updated: 2026/04/17 12:54:55 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

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
void				check_numbers(char **args);

/* flags.c */
void				default_flag(t_flags *flag);
int					are_flags(char *arg);
int					apply_flag(t_flags *flag, char *arg);
int					handle_flags(int argc, char **argv, t_flags *flag,
						int *start);

/* parse.c */
int					read_args(int argc, char **argv, t_flags *flag,
						t_parse *parse);

#endif
