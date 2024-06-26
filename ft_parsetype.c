/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsetype.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:48:30 by epinaud           #+#    #+#             */
/*   Updated: 2024/06/24 20:13:41 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_nbr(int nbr)
{
	ft_putnbr_fd(nbr, 1);
	return (ft_nbrlen(nbr));
}

static int	print_str(char *str)
{
	ft_putstr_fd(str, 1);
	return (ft_strlen(str));
}

static int	print_nbr_base(long long nbr, char *base)
{
	ft_putnbr_base_fd(nbr, base, 1);
	return (ft_nbrlen(nbr));
}

int	ft_printtype_caller(int type, long long *argptr)
{
	//i or d
	if (type == 110 || type == 105)
		return print_nbr((int)*argptr);
	//c
	else if (type == 99)
	{
		ft_putchar_fd((int)*argptr, 1);
		return (1);
	}
	//s
	else if (type == 115)
		return print_str((char *)*argptr);
	//p
	else if (type == 112)
	{	
		if (*argptr == 0)
			return (print_str((char *)*argptr));
		ft_putstr_fd("0x", 1);
		return (print_nbr_base(*argptr, "0123456789abcdef") + 2);
	}
	// x or X
	else if (type == 120)
		return (print_nbr_base(*argptr, "0123456789abcdef"));
	else if (type == 88)
		return (print_nbr_base(*argptr, "0123456789ABCDEF"));
	else
		return (0);
}
