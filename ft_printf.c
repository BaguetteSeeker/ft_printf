/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:42:38 by epinaud           #+#    #+#             */
/*   Updated: 2024/07/22 18:32:48 by epinaud          ###   ########.fr       */
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

static int	ft_eval_pcdr(char *pcdr, va_list *arg, size_t *strlen)
{
	int		pcdr_code;
	size_t	offset;
	va_list	argcpy;

	va_copy(argcpy, *arg);
	offset = 0;
	pcdr_code = ft_parse_type(pcdr, &offset);
	//dirs.type = pcdr_code;
	//if (dirs.left)
		//send argcpy to printdirs
		//ft_prepend_print(dirs);
	*strlen += ft_print_type_router(pcdr_code, *arg);
	return (offset);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	size_t	strlen;
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
			str += ft_parse_dirs((char *)str, args, dirs).offset;
			str += ft_eval_pcdr((char *)str, &args, &strlen);
			continue ;
		}
		ft_putchar_fd(*str++, 1);
		strlen++;
	}
	va_end(args);
	return (strlen);
}
