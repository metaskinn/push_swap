/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 17:05:00 by metaskin          #+#    #+#             */
/*   Updated: 2026/03/15 17:40:49 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "bench.h"

char		**split(char *s);
long		ft_atol(char *str);
int			is_wspace(char c);
void		free_split(char **arr);

#endif
