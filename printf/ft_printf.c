/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:14:08 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/07/06 15:02:15 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_putnbr_base(long long n, char *base, int b)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		write(1, "-", 1);
		n *= -1;
		i = 1;
	}
	if (n / b > 0)
		i += ft_putnbr_base(n / b, base, b);
	write(1, &base[n % b], 1);
	i++;
	return (i);
}

int ft_printf(const char *s, ... )
{
	va_list	args;
	int		i;
	int		counter;

	i = 0;
	counter = 0;
	va_start(args, s);
	while (s[i] != '\0')
	{
		if (s[i] == '%')
		{
			i++;
			if (s[i] == 's')
				counter += ft_putstr(va_arg(args, char *));
			else if (s[i] == 'd')
				counter += ft_putnbr_base(va_arg(args, int), "0123456789", 10);
			else if (s[i] == 'x')
				counter += ft_putnbr_base(va_arg(args, unsigned int), "0123456789abcdef", 16);
		}
		else
		{
			write(1, &s[i], 1);
			counter++;
		}
		i++;
	}
	va_end(args);
	return (counter);
}

