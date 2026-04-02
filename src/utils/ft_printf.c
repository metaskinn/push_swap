/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 02:44:58 by metaskin          #+#    #+#             */
/*   Updated: 2026/04/02 03:08:56 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	ft_putstr(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (ft_putstr("(null)"));
	while (s[i])
		i += ft_putchar(s[i]);
	return (i);
}

static int	ft_putnbr(unsigned long long nbr, const char *base, unsigned int b)
{
	int	count;

	count = 0;
	if (nbr >= (unsigned long long)b)
		count += ft_putnbr(nbr / b, base, b);
	count += ft_putchar(base[nbr % b]);
	return (count);
}

static int	ft_print_ptr(va_list ap)
{
	unsigned long long	ptr;

	ptr = (unsigned long long)va_arg(ap, void *);
	if (ptr == 0)
		return (ft_putstr("(nil)"));
	return (ft_putstr("0x") + ft_putnbr(ptr, "0123456789abcdef", 16));
}

static int	ft_dispatch(char s, va_list ap)
{
	long long	n;

	if (s == 'c')
		return (ft_putchar(va_arg(ap, int)));
	if (s == 's')
		return (ft_putstr(va_arg(ap, char *)));
	if (s == 'u')
		return (ft_putnbr(va_arg(ap, unsigned int), "0123456789", 10));
	if (s == 'x')
		return (ft_putnbr(va_arg(ap, unsigned int), "0123456789abcdef", 16));
	if (s == 'X')
		return (ft_putnbr(va_arg(ap, unsigned int), "0123456789ABCDEF", 16));
	if (s == 'p')
		return (ft_print_ptr(ap));
	if (s == '%')
		return (ft_putchar('%'));
	if (s != 'd' && s != 'i')
		return (0);
	n = (long long)va_arg(ap, int);
	if (n < 0)
		return (ft_putchar('-') + ft_putnbr((unsigned long long)(-n),
			"0123456789", 10));
	return (ft_putnbr((unsigned long long)n, "0123456789", 10));
}

int	ft_printf(const char *format, ...)
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
			count += ft_dispatch(*(++format), ap);
		else if (*format != '%')
			count += ft_putchar(*format);
		format++;
	}
	va_end(ap);
	return (count);
}
