/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asobolev <asobolev@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 22:31:01 by asobolev          #+#    #+#             */
/*   Updated: 2026/03/13 12:54:42 by asobolev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	*ft_memset(void *b, int c, size_t n)
{
	unsigned char	*byte_ptr;

	byte_ptr = (unsigned char *)b;
	while (n--)
		*(byte_ptr++) = (unsigned char)c;
	return (b);
}

size_t	ft_strlen(const char *s)
{
	size_t	idx;

	idx = 0;
	while (s[idx])
		idx++;
	return (idx);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	char		*a;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	i = 0;
	a = malloc((len + 1) * sizeof(char));
	if (!a)
		return (NULL);
	while (i < len)
	{
		a[i] = s[start + i];
		i++;
	}
	a[i] = '\0';
	return (a);
}

char	*ft_strdup(const char *s)
{
	char	*start;
	char	*ptr;

	ptr = malloc(ft_strlen(s) + 1);
	if (!ptr)
		return (NULL);
	start = ptr;
	while (*s)
	{
		*ptr = *s;
		ptr++;
		s++;
	}
	*ptr = '\0';
	return (start);
}
