/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 17:05:00 by metaskin          #+#    #+#             */
/*   Updated: 2026/03/14 06:10:35 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "bench.h"

typedef struct s_parse
{
	char	**args;
	int		need_free;
}			t_parse;

int			args_input(int argc, char **argv, t_flags *flag, t_parse *parse);
char		**split(char *s);
long		ft_atol(char *str);
int			is_wspace(char c);
void		free_split(char **arr);

#endif
