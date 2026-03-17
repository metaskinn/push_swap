/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 17:05:00 by metaskin          #+#    #+#             */
/*   Updated: 2026/03/17 18:46:41 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "bench.h"

char		**split(char *s);
long		ft_atol(char *str);
int			is_wspace(char c);
void		free_split(char **arr);

typedef struct s_parse
{
	char	**args;
	int		must_free;
}			t_parse;

void	check_numbers(char **args);
int		read_args(int argc, char **argv, t_flags *flag, t_parse *parse);

#endif
