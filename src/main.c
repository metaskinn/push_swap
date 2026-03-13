/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asobolev <asobolev@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:22:26 by metaskin          #+#    #+#             */
/*   Updated: 2026/03/14 00:19:48 by asobolev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc < 2)
		return (0);
	return (0);
}
#include "push_swap.h"


int main()
{
   int i=0;
   int number;
   char *strng = "   21 44+ 55 86";

    char **splitend =splitt(strng);

    while(splitend[i]!=NULL)
    {

        if (is_digit(splitend[i])== 0)
           error();
        
        number = ft_atol(splitend[i]);
        if (is_int(number) == 0)
            error();
        i++;
    }
    
}
