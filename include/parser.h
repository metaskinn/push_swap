/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 17:05:00 by metaskin          #+#    #+#             */
/*   Updated: 2026/03/20 16:44:41 by metaskin         ###   ########.fr       */
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
	int				disorder;
}					t_flags;

void				default_flag(t_flags *flag);
int					are_flags(char *arg);
int					apply_flag(t_flags *flag, char *arg);
int					handle_flags(int argc, char **argv, t_flags *flag,
						int *start);

char				**split(char *s);
long				ft_atol(char *str);
int					is_wspace(char c);
void				free_split(char **arr);

typedef struct s_parse
{
	char			**args;
	int				must_free;
}					t_parse;

void				check_numbers(char **args);
int					read_args(int argc, char **argv, t_flags *flag,
						t_parse *parse);

#endif
