/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_padding.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 11:38:57 by epinaud           #+#    #+#             */
/*   Updated: 2024/08/23 15:41:58 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_parse_len(const char *str, va_list *args, int *ldest)
{
	size_t	offset;
	int		n;

	n = 0;
	offset = 0;
	if (str[offset] == '*')
	{
		offset++;
		n = va_arg(*args, int);
	}
	else
		while (ft_isdigit(str[offset]))
			n = (n * 10) + (str[offset++] - '0');
	*ldest = n;
	return (offset);
}

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
	if (ft_strchr(" 0", chr))
		while (i < amount)
			i += write(1, &chr, 1);
	if (amount < 0)
		amount = 0;
	return (amount);
}

static size_t	ft_root_padding(int chr, t_directives dirs)
{
	size_t	spclen;
	size_t	zlen;

	spclen = 0;
	zlen = 0;
	if (!dirs.put_tail)
	{
		if (!dirs.left && chr != '0' && (dirs.precision > -1 || !dirs.zero))
			spclen += dirs.width - dirs.arglen - dirs.siglen;
		if (ft_strchr("diuxXp", dirs.type) && chr == '0')
		{
			if (dirs.precision > -1)
				zlen += dirs.precision - dirs.ndigits;
			else if (dirs.zero)
				zlen += dirs.width - dirs.arglen - dirs.siglen;
		}
	}
	else
		spclen += dirs.width - dirs.strlen;
	return (ft_print_padding(spclen, ' ') + ft_print_padding(zlen, '0'));
}

static size_t	ft_count_signs(long long arg, t_directives dirs)
{
	dirs.siglen = 0;
	if (ft_strchr("diup", dirs.type))
	{
		if (dirs.plus && (arg >= 0 && dirs.type != 'p'))
			dirs.siglen++;
		else if (dirs.plus && (arg && dirs.type == 'p'))
			dirs.siglen++;
		else if ((int)arg < 0 && dirs.type != 'u' && dirs.type != 'p')
			dirs.siglen++;
		else if (dirs.space && (int)arg >= 0)
			dirs.siglen++;
		else if (dirs.type == 'p' && (int)arg != 0)
			dirs.siglen += 2;
	}
	if ((dirs.hash && ft_strchr("xX", dirs.type) && (unsigned int)arg))
		dirs.siglen += 2;
	return (dirs.siglen);
}

size_t	ft_print_directives(long long arg, t_directives dirs)
{
	if (dirs.type == '%')
		return (1);
	dirs.siglen += ft_count_signs((int)arg, dirs);
	dirs.strlen += ft_root_padding(' ', dirs);
	if (!dirs.put_tail)
	{
		if (ft_strchr("iudp", dirs.type))
		{
			if (dirs.plus && ((int)arg >= 0 && dirs.type != 'p'))
				dirs.strlen += write(1, &"+", 1);
			else if (dirs.plus && ((int)arg && dirs.type == 'p'))
				dirs.strlen += write(1, &"+", 1);
			else if ((int)arg < 0 && dirs.type != 'u' && dirs.type != 'p')
				dirs.strlen += write(1, &"-", 1);
			else if (dirs.space && (int)arg >= 0)
				dirs.strlen += write(1, &" ", 1);
			else if (dirs.type == 'p' && arg)
				dirs.strlen += write(1, "0x", 2);
		}
		else if (dirs.hash && ft_strchr("xX", dirs.type) && (unsigned int)arg)
			dirs.strlen += ft_printf("0%c", dirs.type);
		dirs.strlen += ft_root_padding('0', dirs);
	}
	return (dirs.strlen);
}
