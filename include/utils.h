/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 02:03:05 by metaskin          #+#    #+#             */
/*   Updated: 2026/03/14 04:41:00 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>

int		error(void);
int		is_intrange(long num);
int		is_numstr(char *str);
int		has_dup(char **args);

void	*ft_memset(void *b, int c, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s);
void	*ft_calloc(size_t count, size_t size);

int		mt_strcmp(const char *s1, const char *s2);

#endif
