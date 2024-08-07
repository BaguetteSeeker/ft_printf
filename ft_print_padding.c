/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_padding.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 11:38:57 by epinaud           #+#    #+#             */
/*   Updated: 2024/08/07 13:07:34 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_padding(int amount, char chr)
{
	int	i;
	//printf("Amount to print is %d \n",  amount);
	i = 0;
	if (chr == '\b')
	{
		while (i < amount)
		{
			ft_putstr_fd("\b \b", 1);
			//ft_putchar_fd('\b', 1);
			i++;
		}
	}
	else if (ft_strchr(" 0", chr))
		while (i < amount)
			i += write(1, &chr, 1);
	if (amount < 0)
		amount = 0;
	return (amount);
}

size_t	ft_root_padding(int chr, t_directives dirs)
{
	size_t	padlen;

	padlen = 0;
	if (ft_strchr("diuxX", dirs.type))
		dirs.arglen = MAX(dirs.precision, dirs.arglen);
	else if (dirs.type == 's' && dirs.precision != -1)
		dirs.arglen = MIN(dirs.precision, dirs.arglen);
 	//printf("\n Evald Arglen == %d \n Dirs.siglen = %d \n Precision is : %d \n Arg contains %d Ndigits \n", dirs.arglen, dirs.siglen, dirs.precision, dirs.ndigits);
	if (!dirs.put_tail)
	{
		if (!dirs.left && chr != '0')
			padlen += ft_print_padding(dirs.width - dirs.arglen - dirs.siglen, ' ');
		if (ft_strchr("diuxX", dirs.type) && dirs.precision && chr == '0')
			padlen += ft_print_padding(dirs.precision - dirs.ndigits, '0');
	}
	else
	{
		//printf("Dirs precision at puttail padding is : %d \n", dirs.precision);
		if (dirs.type == 's' && dirs.precision != -1)
			padlen -= ft_print_padding(dirs.arglen - dirs.precision, '\b');
		else if (ft_strchr("diuxX", dirs.type) && dirs.precision == 0)
			padlen -= ft_print_padding(1, '\b');
		padlen += ft_print_padding(dirs.width - dirs.outlen, ' ');
	}
	//printf("\n Printed %ld padlen \n", padlen);
	return (padlen);
}
