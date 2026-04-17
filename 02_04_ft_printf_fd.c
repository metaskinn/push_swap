/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_04_ft_printf_fd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 04:25:00 by metaskin          #+#    #+#             */
/*   Updated: 2026/04/16 13:54:58 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdarg.h>
#include <unistd.h>

static int	putstr_fd_local(int fd, const char *s)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (!s)
		return (putstr_fd_local(fd, "(null)"));
	while (s[i])
	{
		count += write(fd, &s[i], 1);
		i++;
	}
	return (count);
}

static int	putnbr_base_fd_local(int fd, unsigned long long n, const char *b,
		unsigned int size)
{
	int	count;

	count = 0;
	if (n >= (unsigned long long)size)
		count += putnbr_base_fd_local(fd, n / size, b, size);
	count += write(fd, &b[n % size], 1);
	return (count);
}

static int	dispatch_unsigned_fd_local(int fd, char c, va_list ap)
{
	if (c == 'u')
		return (putnbr_base_fd_local(fd, va_arg(ap, unsigned int), "0123456789",
				10));
	if (c == 'x')
		return (putnbr_base_fd_local(fd, va_arg(ap, unsigned int),
				"0123456789abcdef", 16));
	if (c == 'X')
		return (putnbr_base_fd_local(fd, va_arg(ap, unsigned int),
				"0123456789ABCDEF", 16));
	if (c == 'p')
		return (putstr_fd_local(fd, "0x") + putnbr_base_fd_local(fd,
				(unsigned long long)va_arg(ap, void *), "0123456789abcdef",
				16));
	if (c == '%')
		return (write(fd, "%", 1));
	return (-1);
}

static int	dispatch_fd_local(int fd, char c, va_list ap)
{
	long long	n;
	char		ch;
	int			unsigned_count;

	if (c == 'c')
	{
		ch = (char)va_arg(ap, int);
		return (write(fd, &ch, 1));
	}
	if (c == 's')
		return (putstr_fd_local(fd, va_arg(ap, char *)));
	unsigned_count = dispatch_unsigned_fd_local(fd, c, ap);
	if (unsigned_count >= 0)
		return (unsigned_count);
	n = (long long)va_arg(ap, int);
	if (n < 0)
		return (write(fd, "-", 1) + putnbr_base_fd_local(fd,
				(unsigned long long)(-n), "0123456789", 10));
	return (putnbr_base_fd_local(fd, (unsigned long long)n, "0123456789", 10));
}

int	ft_printf_fd(int fd, const char *format, ...)
{
	va_list	ap;
	int		count;

	if (!format)
		return (-1);
	va_start(ap, format);
	count = 0;
	while (*format)
	{
		if (*format == '%' && *(format + 1))
			count += dispatch_fd_local(fd, *(++format), ap);
		else if (*format != '%')
			count += write(fd, format, 1);
		format++;
	}
	va_end(ap);
	return (count);
}
