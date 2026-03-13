/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 23:50:34 by metaskin          #+#    #+#             */
/*   Updated: 2026/03/14 01:32:20 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**split(char *s);
char	*ft_strdup(const char *s);

int		error(void);
int		arr_len(char **s);

long	ft_atol(char *str);

int		is_wspace(char c);
int		is_intrange(long num);
int		is_numstr(char *str);

size_t	ft_strlen(const char *s);

void	free_split(char **arr);
void	*ft_memset(void *b, int c, size_t n);
void	*ft_calloc(size_t count, size_t size);

#endif
