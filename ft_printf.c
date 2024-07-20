/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:42:38 by epinaud           #+#    #+#             */
/*   Updated: 2024/07/20 02:50:55 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_parse_type(char *pcdr, size_t *offset)
{
	int	code;

	code = 0;
	while (pcdr[*offset] != ' ' && pcdr[*offset])
	{
		code = code * 10 + pcdr[*offset];
		*offset += 1;
		if (pcdr[*offset] == '%' )
			break ;
	}
	return (code);
}

static int	ft_pcdr_handle(char *pcdr, va_list *arg, size_t *strlen, t_directives dirs)
{
	int		pcdr_code;
	size_t	offset;

	offset = 0;
	pcdr_code = ft_parse_type(pcdr, &offset);
	if (dirs.left)
		ft_print_dirs(dirs);
	if (pcdr_code == '%')
	{
		ft_putchar_fd('%', 1);
		*strlen += 1;
	}
	else
		*strlen += ft_print_type_router(pcdr_code, va_arg(*arg, long long));
	if (!dirs.left)
		ft_print_dirs(dirs);
	return (offset);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	size_t	strlen;
	t_directives dirs;

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
			str += ft_parse_directives((char *)str, args, dirs).offset;
			str += ft_pcdr_handle((char *)str, &args, &strlen, dirs);
			continue ;
		}
		ft_putchar_fd(*str++, 1);
		strlen++;
	}
	va_end(args);
	return (strlen);
}
