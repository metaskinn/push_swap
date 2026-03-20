/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 23:50:34 by metaskin          #+#    #+#             */
/*   Updated: 2026/03/20 16:51:50 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "parser.h"
# include "stack.h"
// # include "utils.h"
// # include "ops.h"
# include <stdlib.h>
# include <unistd.h>

typedef struct s_program
{
	t_stack	a;
	t_stack	b;
	t_flags	flag;
	t_parse	parse;
}			t_program;

#endif
