/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_padding.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 11:38:57 by epinaud           #+#    #+#             */
/*   Updated: 2024/08/05 13:28:44 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_padding(int amount, char chr)
{
	int	i;

	i = 0;
	if (chr == '\b')
	{
		while (i < amount)
		{
			ft_putstr_fd("\b\0\b", 1);
			i++;
		}
		amount = -amount;
	}
	else if (ft_strchr(" 0", chr))
		while (i < amount)
			i += write(1, &chr, 1);
	if (amount < 0)
		amount = 0;
	return (amount);
}

size_t	ft_root_padding(t_directives dirs)
{
	size_t	final_arglen;

	if (ft_strchr("diuxX", dirs.type))
		final_arglen = MAX(dirs.precision, dirs.arglen);
	else if (dirs.type == 's')
		final_arglen = MIN(dirs.precision, dirs.arglen);
	printf("\n Arglen == %d && Final arglen : %ld \n Dirs.siglen = %d \n", dirs.arglen, final_arglen, dirs.siglen);
	if (!dirs.put_tail)
	{
		if (!dirs.left)
			dirs.outlen += ft_print_padding(dirs.width - final_arglen - dirs.siglen, ' ');
		if (ft_strchr("diuxX", dirs.type) && dirs.precision)
			dirs.outlen += ft_print_padding(dirs.precision - dirs.ndigits, '0');
	}
	else
	{
		if (dirs.type == 's')
			dirs.outlen -= ft_print_padding(dirs.arglen - dirs.precision, '\b');
		dirs.outlen += ft_print_padding(dirs.width - dirs.outlen, ' ');
	}
	
	return (dirs.outlen);
}