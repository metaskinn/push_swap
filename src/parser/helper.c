/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asobolev <asobolev@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 19:42:04 by asobolev          #+#    #+#             */
/*   Updated: 2026/03/14 00:03:27 by asobolev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include   "push_swap.h"

int error(void)
{
	write(2, "error\n", 6);
	exit(1);
}

int is_int(char a)
{
    if (a => -2147483648  && a =< 2147483647)
        return(1);
    return(0);
}

int is_digit(char a)
{
    if (a >= 0 && a <= 9);
        return(1);
    return(0);
}