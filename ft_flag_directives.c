/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_directives.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 21:22:55 by epinaud           #+#    #+#             */
/*   Updated: 2024/08/09 19:35:37 by epinaud          ###   ########.fr       */
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
	dirs.precision = -1;
	dirs.hash = 0;
	dirs.space = 0;
	dirs.plus = 0;
	dirs.offset = 0;
	dirs.outlen = 0;
	dirs.siglen = 0;
	dirs.arglen = 0;
	dirs.ndigits = 0;
	dirs.putnull = 0;
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

static size_t	ft_count_signs(long long arg, t_directives dirs)
{
	dirs.siglen = 0;
	if (ft_strchr("diup", dirs.type))
	{
		if (dirs.plus && ((arg >= 0 && dirs.type != 'p') || (arg && dirs.type == 'p')))
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

static size_t	ft_fetch_arglen(long long arg, int type, int putnull)
{
	size_t	arglen;
	
	arglen = 0;
	if (type == 's' && (char *)arg)
		arglen = ft_strlen((char *)arg);
	else if (type == 's' && !(char *)arg && putnull)
		arglen = 6;
	else if (type == 'p' && !(unsigned long)arg)
		arglen = 5;
	else if (ft_strchr("p", type))
		arglen = ft_nbrblen((unsigned long)arg, 16);
	else if (ft_strchr("xX", type))
		arglen = ft_nbrblen((unsigned int)arg, 16);
	else if (type == 'c' || type == '%')
		arglen = 1;
	else if (type == 'u')
		arglen = ft_nbrlen(0xffffffff + (unsigned int)arg + 1);
	else if (type == 'd' || type == 'i')
		arglen = ft_nbrdig((int)arg);
	//printf("Arglen is %ld \n" , arglen);
	return (arglen);
}

size_t	ft_print_directives(long long arg, t_directives dirs)
{
	//printf("Fetched arglen is %ld \n", ft_fetch_arglen(arg, dirs.type));
	dirs.siglen = ft_count_signs((int)arg, dirs);
	dirs.outlen += ft_root_padding(' ', dirs);
	//printf("Siglen in printd dirs is %d \n", dirs.siglen);
	if (!dirs.put_tail)
	{
		if (ft_strchr("iudp", dirs.type))
		{
			if (dirs.plus && (((int)arg >= 0 && dirs.type != 'p') || ((int)arg && dirs.type == 'p')))
				dirs.outlen += write(1, &"+", 1);
			else if ((int)arg < 0 && dirs.type != 'u' && dirs.type != 'p')
				dirs.outlen += write(1, &"-", 1);
			else if (dirs.space && (int)arg >= 0)
				dirs.outlen += write(1, &" ", 1);
			else if (dirs.type == 'p' && arg)
				dirs.outlen += write(1, "0x", 2);
		}
		else if (dirs.hash && ft_strchr("xX", dirs.type) && (unsigned int)arg)
			dirs.outlen += ft_printf("0%c", dirs.type);
		dirs.outlen += ft_root_padding('0', dirs);
	}
	
	//printf("Actual outlen is %d \n", dirs.outlen);
	return (dirs.outlen);
}

static int	ft_parse_len(const char *str, int offset, va_list args, int *ldest)
{
	int	n;

	n = 0;
	if (str[offset] == '*')
	{
		offset++;
		n = va_arg(args, int);
	}
	else
		while (ft_isdigit(str[offset]))
			n = (n * 10) + (str[offset++] - '0');
	*ldest = n;
	return (offset);
}

t_directives	ft_parse_dirs(const char *str, va_list args, t_directives *dirs)
{
	va_list	argcpy;
	long long	arg;

	va_copy(argcpy, args);
	arg = va_arg(argcpy, long long);
	while (ft_strchr("-#+ 0", str[dirs->offset]))
		*dirs = ft_parse_flags(&str[dirs->offset++], *dirs);
	dirs->offset = ft_parse_len(str, dirs->offset, args, &dirs->width);
	if (str[dirs->offset] == '.' )
	{
		dirs->precision = 0;
		dirs->offset++;
		dirs->offset = ft_parse_len(str, dirs->offset, args, &dirs->precision);
		if (ft_strchr("pxX", str[dirs->offset]))
			dirs->ndigits = ft_nbrblen((unsigned int)arg, 16);
		else if (ft_strchr("id", str[dirs->offset]))
			dirs->ndigits = ft_nbrdig((int)arg);
		else if (str[dirs->offset] == 'u')
			dirs->ndigits = ft_nbrlen((unsigned int)arg);
		//printf("Ndigits are : %d \n", dirs->ndigits);
	}
	if (ft_strchr("cspuidxX%", str[dirs->offset]))
		dirs->type = str[dirs->offset];
	if (dirs->type == 's' && !(char *)arg && (dirs->precision >= 6 || dirs->precision == -1))
		dirs->putnull = 1;
	dirs->arglen = ft_fetch_arglen(arg, dirs->type, dirs->putnull);
	if (ft_strchr("diuxX", dirs->type) && (int)arg == 0 && dirs->precision == 0)
		dirs->arglen = 0;
	else if (ft_strchr("diuxXp", dirs->type))
		dirs->arglen = MAX(dirs->precision, dirs->arglen);
	else if (dirs->type == 's' && dirs->precision > -1 && (char *)arg != 0)
		dirs->arglen = MIN(dirs->precision, dirs->arglen);
	//printf("Arglen are : %d \n", dirs->arglen);
	va_end(argcpy);
	return (*dirs);
}
