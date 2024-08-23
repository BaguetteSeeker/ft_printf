/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_directives.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 21:22:55 by epinaud           #+#    #+#             */
/*   Updated: 2024/08/23 15:43:54 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	ft_parse_flags(const char *str, t_directives *dirs)
{
	size_t	offset;

	offset = 0;
	while (ft_strchr("-#+ 0", str[offset]))
	{
		if (*str == '-')
			dirs->left = '1';
		else if (*str == '#')
			dirs->hash = 1;
		else if (*str == ' ')
			dirs->space = 1;
		else if (*str == '+')
			dirs->plus = 1;
		else if (*str == '0')
			dirs->zero = 1;
		offset++;
	}
	return (offset);
}

static size_t	ft_fetch_arglen(long long arg, t_directives dirs)
{
	size_t	arglen;

	arglen = 0;
	if (dirs.type == 's' && (char *)arg)
		arglen = ft_strlen((char *)arg);
	else if (dirs.type == 's' && !(char *)arg && dirs.putnull)
		arglen = 6;
	else if (dirs.type == 'p' && !(unsigned long)arg)
		arglen = 5;
	else if (ft_strchr("p", dirs.type))
		arglen = ft_nbrblen((unsigned long)arg, 16);
	else if (ft_strchr("xX", dirs.type))
		arglen = ft_nbrblen((unsigned int)arg, 16);
	else if (dirs.type == 'c' || dirs.type == '%')
		arglen = 1;
	else if (dirs.type == 'u')
		arglen = ft_nbrlen(0xffffffff + (unsigned int)arg + 1);
	else if (dirs.type == 'd' || dirs.type == 'i')
		arglen = ft_nbrdig((int)arg);
	return (arglen);
}

static int	eval_arglen(va_list *args, t_directives *dirs)
{
	va_list	argcpy;
	va_list	argccpy;

	va_copy(argcpy, *args);
	va_copy(argccpy, argcpy);
	dirs->arglen = ft_fetch_arglen(va_arg(argccpy, long long), *dirs);
	if (ft_strchr("diuxXp", dirs->type) && dirs->precision != 0)
		dirs->arglen = ft_maxint(dirs->precision, dirs->arglen);
	if (dirs->type == 's' && dirs->precision > -1)
		if (va_arg(argcpy, char *) != 0)
			dirs->arglen = ft_minint(dirs->precision, dirs->arglen);
	va_end(argcpy);
	va_end(argccpy);
	return (dirs->arglen);
}

static int	parse_precision(va_list *args, t_directives *dirs, const char *str)
{
	va_list	argcpy;

	va_copy(argcpy, *args);
	dirs->precision = 0;
	dirs->offset++;
	dirs->offset += ft_parse_len(&str[dirs->offset], args, &dirs->precision);
	if (ft_strchr("pxX", str[dirs->offset]))
		dirs->ndigits = ft_nbrblen(va_arg(argcpy, unsigned int), 16);
	else if (ft_strchr("id", str[dirs->offset]))
		dirs->ndigits = ft_nbrdig(va_arg(argcpy, int));
	else if (str[dirs->offset] == 'u')
		dirs->ndigits = ft_nbrlen(va_arg(argcpy, unsigned int));
	va_end(argcpy);
	return (dirs->offset);
}

t_directives	ft_parse_dirs(char *str, va_list *args, t_directives *dirs)
{
	va_list	argcpy;

	va_copy(argcpy, *args);
	dirs->offset = ft_parse_flags(str, dirs);
	dirs->offset += ft_parse_len(&str[dirs->offset], args, &dirs->width);
	if (str[dirs->offset] == '.' )
		parse_precision(args, dirs, str);
	if (ft_strchr("cspuidxX%", str[dirs->offset]))
		dirs->type = str[dirs->offset++];
	dirs->putnull = 1;
	if (!(dirs->type == 's' && !va_arg(argcpy, char *)))
		dirs->putnull = 0;
	else if (!(dirs->precision >= 6 || dirs->precision == -1))
		dirs->putnull = 0;
	eval_arglen(args, dirs);
	va_end(argcpy);
	return (*dirs);
}
