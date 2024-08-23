/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:42:38 by epinaud           #+#    #+#             */
/*   Updated: 2024/08/23 14:51:23 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*static int	ft_parse_type(char *pcdr, size_t *offset)
{
	int	code;

	code = 0;
	while (pcdr[*offset] && ft_strchr("cspuidxX%", pcdr[*offset]))
	{
		code = code * 10 + pcdr[*offset];
		*offset += 1;
		if (pcdr[*offset] == '%' )
			break ;
		break ;
	}
	return (code);
}*/
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
	dirs.strlen = 0;
	dirs.siglen = 0;
	dirs.arglen = 0;
	dirs.ndigits = 0;
	dirs.putnull = 0;
	dirs.put_tail = 0;
	return (dirs);
}

static int	ft_eval_pcdr(size_t *strlen, va_list *arg, t_directives dirs)
{
	va_list		argcpy;
	long long	argval;

	va_copy(argcpy, *arg);
	argval = va_arg(argcpy, long long);
	dirs.strlen += ft_print_directives(argval, dirs);
	if (!(dirs.precision == 0 && argval == 0 && ft_strchr("diuxX", dirs.type)))
		dirs.strlen += ft_print_type_router(arg, dirs);
	dirs.put_tail = 1;
	dirs.strlen = ft_print_directives(argval, dirs);
	*strlen += dirs.strlen;
	va_end(argcpy);
	return (dirs.strlen);
}

int	ft_printf(const char *str, ...)
{
	va_list			args;
	size_t			strlen;
	t_directives	dirs;

	if (!str)
		return (0);
	va_start(args, str);
	strlen = 0;
	while (*str)
	{
		if (*str == '%' && str[1])
		{
			str++;
			dirs = ft_init_directives(dirs);
			str += ft_parse_dirs((char *)str, &args, &dirs).offset;
			ft_eval_pcdr(&strlen, &args, dirs);
			continue ;
		}
		ft_putchar_fd(*str++, 1);
		strlen++;
	}
	va_end(args);
	return (strlen);
}
