/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:48:30 by epinaud           #+#    #+#             */
/*   Updated: 2024/08/01 12:56:16 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_nbr(int nbr, int type)
{
	long int	ulnb;

	if (type == 'u')
	{
		if (nbr < 0)
		{
			ulnb = 0xffffffff + nbr + 1;
			ft_putnbr_fd(ulnb, 1, 1);
			return (ft_nbrlen(ulnb));
		}
	}
	ft_putnbr_fd(nbr, 1, 1);
	return (ft_nbrlen(nbr));
}

static int	print_str(char *str)
{
	if (str == 0)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	ft_putstr_fd(str, 1);
	return (ft_strlen(str));
}

static int	print_ptr(unsigned long long nbr, char *base)
{
	if (nbr == 0)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	ft_putstr_fd("0x", 1);
	return (ft_putnbr_base_fd(nbr, base, 1) + 2);
}

static int	print_hex(unsigned int n, char *base)
{
	return (ft_putnbr_base_fd(n, base, 1));
}

int	ft_print_type_router(int type, va_list arg)
{
	if (type == '%')
		return (write(1, &"%", 1));
	else if (type == 'd' || type == 'i' || type == 'u')
		return (print_nbr(va_arg(arg, long long), type));
	else if (type == 'c')
	{
		ft_putchar_fd(va_arg(arg, int), 1);
		return (1);
	}
	else if (type == 's')
		return (print_str(va_arg(arg, char*)));
	else if (type == 'p')
		return (print_ptr(va_arg(arg, unsigned long), "0123456789abcdef"));
	else if (type == 'x')
		return (print_hex(va_arg(arg, unsigned int), "0123456789abcdef"));
	else if (type == 'X')
		return (print_hex(va_arg(arg, unsigned int), "0123456789ABCDEF"));
	else
		return (0);
}
