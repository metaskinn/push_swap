/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asobolev <asobolev@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:22:26 by metaskin          #+#    #+#             */
/*   Updated: 2026/03/13 23:15:12 by asobolev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int main()
{
   int i=0;
   int len;
   int atol;
   char *strng = "   21 44+ 55 86";
   

    char **splitend =splitt(strng);
    len = arr_len(splitend);
    
     printf("%d",len);
     
    while(splitend[i]!=NULL)
    {
        
        printf(" ");
        atol=ft_atol(splitend[i])
        i++;
    }
    
}
