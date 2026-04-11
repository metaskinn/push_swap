/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 02:03:05 by metaskin          #+#    #+#             */
/*   Updated: 2026/04/02 03:06:29 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

/* checks.c */
int		error(void);
int		is_intranger_range(long num);
int		is_numstr(char *str);
int		has_dup(char **args);

/* oldfuncs.c */
void	*ft_memset(void *b, int c, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s);
void	*ft_calloc(size_t count, size_t size);

/* newfuncs.c */
int		ft_strcmp(const char *s1, const char *s2);

int		ft_printf_fd(int fd, const char *format, ...);

#endif
