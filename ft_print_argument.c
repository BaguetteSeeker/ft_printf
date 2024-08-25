/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_argument.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:48:30 by epinaud           #+#    #+#             */
/*   Updated: 2024/08/25 16:06:46 by epinaud          ###   ########.fr       */
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
			return (ft_nbrdig(ulnb));
		}
	}
	ft_putnbr_fd(nbr, 1, 1);
	return (ft_nbrdig(nbr));
}

static int	print_str(char *str, size_t cap, int putnull)
{
	if (str == 0)
	{
		if (!putnull)
			return (0);
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	ft_putstrcap_fd(str, cap, 1);
	return (cap);
}

static int	print_ptr(unsigned long nbr, char *base)
{
	if (nbr == 0)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	return (ft_putnbr_base_fd(nbr, base, 1));
}

static int	print_hex(unsigned int n, char *base)
{
	return (ft_putnbr_base_fd(n, base, 1));
}

int	ft_print_arg(va_list *arg, t_directives dirs)
{
	if (dirs.type == '%')
		return (write(1, &"%", 1));
	else if (dirs.type == 'd' || dirs.type == 'i' || dirs.type == 'u')
		return (print_nbr(va_arg(*arg, long long), dirs.type));
	else if (dirs.type == 'c')
	{
		ft_putchar_fd(va_arg(*arg, int), 1);
		return (1);
	}
	else if (dirs.type == 's')
		return (print_str(va_arg(*arg, char *), dirs.arglen, dirs.putnull));
	else if (dirs.type == 'p')
		return (print_ptr(va_arg(*arg, unsigned long), "0123456789abcdef"));
	else if (dirs.type == 'x')
		return (print_hex(va_arg(*arg, unsigned int), "0123456789abcdef"));
	else if (dirs.type == 'X')
		return (print_hex(va_arg(*arg, unsigned int), "0123456789ABCDEF"));
	else
		return (0);
}
