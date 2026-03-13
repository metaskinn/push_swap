/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asobolev <asobolev@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 19:42:04 by asobolev          #+#    #+#             */
/*   Updated: 2026/03/13 20:40:19 by asobolev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include   "push_swap.h"

int arr_len(char **s)
{
    int i;

    i = 0;
    while (arr[i] != NULL)
        i++;
    return(i);
}

int is digit(char a)
{
    if (a => '48' && a =< '57')
        return(1);
    return(0);
}