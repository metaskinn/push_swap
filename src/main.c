/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asobolev <asobolev@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:22:26 by metaskin          #+#    #+#             */
/*   Updated: 2026/03/14 00:25:46 by asobolev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	int		i;
	int		atol;
	char	*strng;
	char	**splitend;

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
