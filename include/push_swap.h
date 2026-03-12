/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asobolev <asobolev@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 23:50:34 by metaskin          #+#    #+#             */
/*   Updated: 2026/03/13 00:31:38 by asobolev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>


char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s);
char	**splitt(char *s);
char	*ft_strdup(const char *s);

int		error(void);

long	ft_atol(char *str);

int 	is_wspace(char c);

size_t	ft_strlen(const char *s);

void	free_split(char **arr);
void	*ft_memset(void *b, int c, size_t n);


#endif
