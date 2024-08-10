/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:42:38 by epinaud           #+#    #+#             */
/*   Updated: 2024/08/10 09:45:04 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_parse_type(char *pcdr, size_t *offset)
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
}

static int	ft_eval_pcdr(char *pcdr, va_list *arg, size_t *strlen, t_directives dirs)
{
	size_t	offset;
	va_list	argcpy;
	int		pcdr_code;
	long long		argval;

	va_copy(argcpy, *arg);
	argval = va_arg(argcpy, long long);
	offset = 0;
	pcdr_code = ft_parse_type(pcdr, &offset);
	if (pcdr_code != '%')
		dirs.outlen += ft_print_directives(argval, dirs);
	if (!(dirs.precision == 0 && argval == 0 && ft_strchr("diuxX", dirs.type)))
		dirs.outlen += ft_print_type_router(pcdr_code, *arg, dirs.arglen, dirs.putnull);
	dirs.put_tail = 1;
	if (pcdr_code != '%')
		dirs.outlen = ft_print_directives(argval, dirs);
	*strlen += dirs.outlen;
	return (offset);
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
			str += ft_parse_dirs((char *)str, args, &dirs).offset;
			str += ft_eval_pcdr((char *)str, &args, &strlen, dirs);
			continue ;
		}
		ft_putchar_fd(*str++, 1);
		strlen++;
	}
	va_end(args);
	return (strlen);
}
