/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_directives.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 21:22:55 by epinaud           #+#    #+#             */
/*   Updated: 2024/07/22 18:35:47 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_directives	ft_init_directives(t_directives dirs)
{
	dirs.type = 0;
	dirs.width = 0;
	dirs.left = 0;
	dirs.zero = 0;
	dirs.star = 0;
	dirs.precision = 0;
	dirs.hash = 0;
	dirs.space = 0;
	dirs.plus = 0;
	dirs.offset = 0;
	return (dirs);
}

static t_directives	ft_parse_flags(const char *str, t_directives dirs)
{
	if (*str == '-')
		dirs.left = '1';
	else if (*str == '#')
		dirs.hash = 1;
	else if (*str == ' ')
		dirs.space = 1;
	else if (*str == '+')
		dirs.plus = 1;
	else if (*str == '0' && dirs.width == 0)
		dirs.zero = 1;
	return (dirs);
}

size_t	ft_print_padding(size_t len, t_directives dirs)
{
	char	chr;

	if (dirs.zero && !dirs.precision)
		chr = 0;
	else if (dirs.space)
		chr = ' ';
	dirs.width = len;
	while (len > 0)
	{
		ft_putchar_fd(chr, 1);
		len--;
	}
	return (dirs.width);
}

size_t	ft_prepend_print(long long arg, t_directives dirs)
{
	size_t	padlen;
	size_t	outlen;

	if (dirs.type == 's')
		padlen = dirs.width - ft_strlen((char *)arg);
	else
		padlen = dirs.width - ft_nbrlen(arg);
	outlen = padlen;
	if (strchr("iud", dirs.type))
	{
		if (dirs.plus && arg >= 0)
			padlen -= write(1, &"+", 1);
		else if (dirs.plus && arg < 0)
			padlen -= write(1, &"-", 1);
			//manage negative sign related to putnbr
		else if (dirs.space && arg >= 0)
			padlen -= write(1, &" ", 1);
	}
	else if (dirs.hash && ft_strchr("xX", dirs.type))
		padlen -= ft_printf("0%c", dirs.type);
	if (!dirs.left && padlen > 0)
		ft_print_padding(padlen, dirs);
	return (outlen);
}

/*void	ft_print_dirs(t_directives dirs)
{
	if (dirs.zero && !dirs.left)
		ft_putchar_fd('\0', 1);

	if (dirs.space && !dirs.left && !dirs.plus)
		print minus for neg or 1 space for pos num 

	if (dirs.hash && ft_strchr("xX", dirs.type))
	{
		ft_putchr('0');
		ft_putchar(dirs.type);
	}
	//check
}*/

static int	ft_parse_len(const char *str, va_list args, int offset, int *ldest)
{
	if (str[offset] == '*')
	{
		offset++;
		*ldest = va_arg(args, int);
	}
	else
		while (ft_isdigit(str[offset]))
			*ldest = (*ldest * 10) + (str[offset++] - '0');
	return (offset);
}

t_directives	ft_parse_dirs(const char *str, va_list args, t_directives dirs)
{
	while (ft_strchr("-#+ 0", str[dirs.offset]))
		dirs = ft_parse_flags(&str[dirs.offset++], dirs);
	dirs.offset += ft_parse_len(str, args, dirs.offset, &dirs.width);
	if (str[dirs.offset] == '.' )
	{
		dirs.offset++;
		dirs.offset += ft_parse_len(str, args, dirs.offset, &dirs.precision);
	}
	if (ft_strchr("cspuidxX%", str[dirs.offset]))
	{
		//add error management
		dirs.type = str[dirs.offset];
	}
	return (dirs);
}
