/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 16:20:00 by metaskin          #+#    #+#             */
/*   Updated: 2026/03/17 18:02:50 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

// bak
int	read_args(int argc, char **argv, t_flags *flag)
{
	int	start;

	default_flag(flag);
	if (!handle_flags(argc, argv, flag, &start))
		error();
	if (start >= argc)
		return (0);
	return (1);
}
