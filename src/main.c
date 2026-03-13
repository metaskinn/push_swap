/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asobolev <asobolev@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:22:26 by metaskin          #+#    #+#             */
/*   Updated: 2026/03/13 23:58:57 by asobolev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int main()
{
   int i=0;
   int atol;
   char *strng = "   21 44+ 55 86";

    char **splitend =splitt(strng);

    while(splitend[i]!=NULL)
    {

        if (is_int(atol) == 0)
           error();
        i++;
    }
    
}
