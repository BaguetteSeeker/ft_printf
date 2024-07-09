/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:42:38 by epinaud           #+#    #+#             */
/*   Updated: 2024/07/06 18:52:05 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_pcdr_handle(char *pcdr, va_list *arg, size_t *strlen)
{
	int		pcdr_code;
	size_t	offset;

	pcdr_code = 0;
	offset = 0;
	while (pcdr[offset] != ' ' && pcdr[offset])
	{
		pcdr_code = pcdr_code * 10 + pcdr[offset++];
		if (pcdr[offset] == '%' )
			break ;
	}
	if (pcdr_code == 99)
	{
		ft_putchar_fd(va_arg(*arg, int), 1);
		*strlen += 1;
	}
	else if (pcdr_code == 37)
	{
		ft_putchar_fd('%', 1);
		*strlen += 1;
	}
	else
		*strlen += ft_printtype_rooter(pcdr_code, va_arg(*arg, long long));
	return (offset);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	size_t	strlen;

	if (!str)
		return (0);
	va_start(args, str);
	strlen = 0;
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			str += ft_pcdr_handle((char *)str, &args, &strlen);
			continue ;
		}
		ft_putchar_fd(*str++, 1);
		strlen++;
	}
	va_end(args);
	return (strlen);
}
