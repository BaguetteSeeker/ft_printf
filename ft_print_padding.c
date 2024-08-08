/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_padding.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 11:38:57 by epinaud           #+#    #+#             */
/*   Updated: 2024/08/08 22:34:04 by epinaud          ###   ########.fr       */
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
	if (ft_strchr("diuxXp", dirs.type))
		dirs.arglen = MAX(dirs.precision, dirs.arglen);
 	//printf("\n Evald Arglen == %d \n Dirs.siglen = %d \n Precision is : %d \n Zero presence is %d \n Arg contains %d Ndigits \n", dirs.arglen, dirs.siglen, dirs.precision, dirs.zero, dirs.ndigits);
	if (!dirs.put_tail)
	{
		if (!dirs.left && chr != '0' && (dirs.precision > -1 || !dirs.zero))
			padlen += ft_print_padding(dirs.width - dirs.arglen - dirs.siglen, ' ');
		if (ft_strchr("diuxXp", dirs.type) && chr == '0')
		{
			if (dirs.precision > -1)
				padlen += ft_print_padding(dirs.precision - dirs.ndigits, '0');
			else if (dirs.zero)
				padlen += ft_print_padding(dirs.width - dirs.arglen - dirs.siglen, '0');
		}
	}
	else
	{
		//printf("\n Arglen is %d at Putail \n Precision at puttail padding is : %d \n", dirs.arglen, dirs.precision);
		if (dirs.type == 's' && dirs.precision != -1)
			padlen -= ft_print_padding(dirs.arglen - dirs.precision, '\b');
		else if (ft_strchr("diuxX", dirs.type) && dirs.precision == 0)
			padlen -= ft_print_padding(1, '\b');
		padlen += ft_print_padding(dirs.width - dirs.outlen, ' ');
				//printf("Padlen is %ld \n outlen is %d \n", padlen, dirs.outlen);
	}
	//printf("\n Printed %ld padlen \n", padlen);
	return (padlen);
}
