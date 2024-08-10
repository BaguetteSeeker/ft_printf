/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_padding.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 11:38:57 by epinaud           #+#    #+#             */
/*   Updated: 2024/08/10 09:20:25 by epinaud          ###   ########.fr       */
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
			ft_putstr_fd("\b \b", 1);
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
		padlen += ft_print_padding(dirs.width - dirs.outlen, ' ');
	return (padlen);
}
