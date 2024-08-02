/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_directives.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 21:22:55 by epinaud           #+#    #+#             */
/*   Updated: 2024/08/02 17:23:03 by epinaud          ###   ########.fr       */
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
	dirs.outlen = 0;
	dirs.arglen = 0;
	dirs.ndigits = 0;
	dirs.put_tail = 0;
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
	else if (*str == '0')
		dirs.zero = 1;
	return (dirs);
}

size_t	ft_print_directives(long long arg, t_directives dirs)
{
	//Rework all padding and out / padlen transfer. Might transfer finalarglen
	if (!dirs.put_tail)
	{
		if (dirs.type == 's' && (char *)arg)
			dirs.arglen = ft_strlen((char *)arg);
		else if (dirs.type)
			dirs.arglen = ft_nbrlen((int)arg);
		if (ft_strchr("iud", dirs.type))
		{
			//printf("TYPE IS : %d", dirs.type);
			//printf("ARG IS : %lld", arg);
			if (dirs.plus && arg >= 0)
				dirs.outlen += write(1, &"+", 1);
			else if ((int)arg < 0 && dirs.type != 'u')
				dirs.outlen += write(1, &"-", 1) - 1;
			else if (dirs.space && arg >= 0)
				dirs.outlen += write(1, &" ", 1);
		}
		else if (dirs.hash && ft_strchr("xX", dirs.type))
			dirs.outlen += ft_printf("0%c", dirs.type);
		dirs.put_tail = 1;
	}
	// track padlen and check if theres any left
	//if (1)
		//dirs.outlen += ft_root_padding(dirs);
	return (dirs.outlen);
}

static int	ft_parse_len(const char *str, va_list args, int *ldest)
{
	int	offset;
	
	offset = 0;
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

t_directives	ft_parse_dirs(const char *str, va_list args, t_directives *dirs)
{
	va_list	argcpy;

	va_copy(argcpy, args);
	while (ft_strchr("-#+ 0", str[dirs->offset]))
		*dirs = ft_parse_flags(&str[dirs->offset++], *dirs);
	dirs->offset += ft_parse_len(str, args, &dirs->width);
		//printf("\n Offset added post parse len is : %d", dirs->offset);
	if (str[dirs->offset] == '.' )
	{
		dirs->offset++;
		dirs->offset += ft_parse_len(str, args, &dirs->precision);
		if (ft_strchr("px", str[dirs->offset]))
			dirs->ndigits = ft_count_digits(ft_itoa_base(va_arg(argcpy, long int), "0123456789abcdef"));
		else if (ft_strchr("X", str[dirs->offset]))
			dirs->ndigits = ft_count_digits(ft_itoa_base(va_arg(argcpy, long int), "0123456789ABCDEF"));
	}
	if (ft_strchr("cspuidxX%", str[dirs->offset]))
		dirs->type = str[dirs->offset];
	va_end(argcpy);
	return (*dirs);
}
