
#include "../../push_swap.h"

bool	is_wspace(char c)
{
	if (c=='\t' || c=='\n' || c=='\v' || c=='\r'|| c=='\f' || c==' ')
		return (true);
	return (false);
}

size_t	ft_strlen(const char *s)
{
	size_t	idx;

	idx = 0;
	while (s[idx])
		idx++;
	return (idx);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dst_bytes;
	unsigned char	*src_bytes;
	size_t			idx;

	if (!dst && !src)
		return (NULL);
	dst_bytes = (unsigned char *)dst;
	src_bytes = (unsigned char *)src;
	idx = 0;
	while (n--)
	{
		dst_bytes[idx] = src_bytes[idx];
		idx++;
	}
	return (dst);
}

char	*ft_strdup(const char *s1)
{
	char	*dup;
	size_t	len;

	len = ft_strlen(s1);
	dup = (char *)malloc(sizeof(char) * (len + 1));
	if (dup == NULL)
		return (NULL);
	ft_memcpy(dup, s1, len + 1);
	return (dup);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	src_len;
	size_t	sub_len;
	char	*sub;

	if (!s)
		return (NULL);
	src_len = ft_strlen(s);
	if (start >= src_len)
		return (ft_strdup(""));
	sub_len = src_len - start;
	if (len < sub_len)
		sub_len = len;
	sub = (char *)malloc(sub_len + 1);
	if (!sub)
		return (NULL);
	ft_memcpy(sub, s + start, sub_len);
	sub[sub_len] = '\0';
	return (sub);
}

void	*ft_memset(void *b, int c, size_t n)
{
	unsigned char	*byte_ptr;

	byte_ptr = (unsigned char *)b;
	while (n--)
		*(byte_ptr++) = (unsigned char)c;
	return (b);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;
	size_t	total;

	if (size != 0 && count > (size_t)-1 / size)
		return (NULL);
	total = count * size;
	mem = malloc(total);
	if (!mem)
		return (NULL);
	ft_memset(mem, 0, total);
	return (mem);
}

static size_t	count_tokens(char const *str)
{
	size_t	count;

	count = 0;
	while (*str)
	{
		while (*str && is_wspace(*str))
			str++;
		if (*str)
			count++;
		while (*str && !is_wspace(*str))
			str++;
	}
	return (count);
}

static char	**free_split(char **tokens, size_t used)
{
	while (used)
		free(tokens[--used]);
	free(tokens);
	return (NULL);
}

char	**ft_split(char const *s)
{
	char		**tokens;
	size_t		tok_idx;
	char const	*tok_st;

	if (!s)
		return (NULL);
	tokens = ft_calloc(count_tokens(s, c) + 1, sizeof(*tokens));
	if (!tokens)
		return (NULL);
	tok_idx = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		tok_st = s;
		while (*s && *s != c)
			s++;
		if (s > tok_st)
		{
			tokens[tok_idx] = ft_substr(tok_st, 0, (size_t)(s - tok_st));
			if (!tokens[tok_idx++])
				return (free_split(tokens, tok_idx - 1));
		}
	}
	return (tokens);
}
