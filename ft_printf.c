/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:42:38 by epinaud           #+#    #+#             */
/*   Updated: 2024/07/17 21:27:03 by epinaud          ###   ########.fr       */
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

static int	ft_pcdr_handle(char *pcdr, va_list *arg, size_t *strlen)
{
	int		pcdr_code;
	size_t	offset;

	offset = 0;
	pcdr_code = ft_parse_type(pcdr, &offset);
	if (pcdr_code == '%')
	{
		ft_putchar_fd('%', 1);
		*strlen += 1;
	}
	else
		*strlen += ft_print_type_router(pcdr_code, va_arg(*arg, long long));
	return (offset);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	size_t	strlen;
	t_directives dirs;

	if (!str)
		return (0);
	strlen = 0;
	ft_init_directives(dirs);
	va_start(args, str);
	while (*str)
	{
		if (*str == '%' && str[1])
		{
			str++;
			str += ft_parse_directives((char *)str, &args, dirs).offset;
			ft_print_prefix(dirs);
			str += ft_pcdr_handle((char *)str, &args, &strlen);
			ft_print_suffix(dirs);
			continue ;
		}
		ft_putchar_fd(*str++, 1);
		strlen++;
	}
	va_end(args);
	return (strlen);
}
