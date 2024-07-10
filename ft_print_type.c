/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:48:30 by epinaud           #+#    #+#             */
/*   Updated: 2024/07/10 18:15:21 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_nil(int ntype)
{
	if (ntype == 5)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	else
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
}

static int	print_nbr(int nbr, int type)
{
	long int	ulnb;

	if (type == 'u')
	{
		if (nbr < 0)
		{
			ulnb = 0xffffffff + nbr + 1;
			ft_putnbr_fd(ulnb, 1);
			return (ft_nbrlen(ulnb));
		}
	}
	ft_putnbr_fd(nbr, 1);
	return (ft_nbrlen(nbr));
}

static int	print_str(char *str)
{
	if (str == 0)
		return (print_nil(6));
	ft_putstr_fd(str, 1);
	return (ft_strlen(str));
}

static int	print_ptr(unsigned long long nbr, char *base)
{
	if (nbr == 0)
		return (print_nil(5));
	ft_putstr_fd("0x", 1);
	return (ft_putnbr_base_fd(nbr, base, 1) + 2);
}

int	ft_print_type_router(int type, long long argptr)
{
	if (type == 'd' || type == 'i' || type == 'u')
		return (print_nbr(argptr, type));
	else if (type == 'c')
	{
		ft_putchar_fd((int)argptr, 1);
		return (1);
	}
	else if (type == 's')
		return (print_str((char *)argptr));
	else if (type == 'p')
		return (print_ptr((unsigned long)argptr, "0123456789abcdef"));
	else if (type == 'x')
		return (ft_putnbr_base_fd((unsigned int)argptr, "0123456789abcdef", 1));
	else if (type == 'X')
		return (ft_putnbr_base_fd((unsigned int)argptr, "0123456789ABCDEF", 1));
	else
		return (0);
}
