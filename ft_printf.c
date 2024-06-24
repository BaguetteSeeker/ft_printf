/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:42:38 by epinaud           #+#    #+#             */
/*   Updated: 2024/06/18 16:42:41 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_map_str(char *str, int (*f)(int))
{
	char	*str_head;

	str_head = str;
	while (*str)
	{
		*str = f(*str);
		str++;
	}
	return (str_head);
}

/*static int	ft_parse_pcdr(char *pcdr_start)
{
	size_t	offset;

	while (*pcdr_start != ' ' && *pcdr_start)
	{
		pcdr_start++;
		offset++;
	}
	return (offset);
}*/

static int	ft_pcdr_handle(char *pcdr, void *arg, size_t *strlen)
{
	char	*paramset;
	int		pcdr_code;
	size_t	offset;

	paramset = "cspdiuxX%";
	pcdr_code = 0;
	offset = 0;
	while (pcdr[offset] != ' ' && pcdr[offset] != '\0')
			pcdr_code = pcdr_code * 10 + pcdr[offset++];
	printf("PCDR CODE IS : %d \n\n\n\n\n\n\n", pcdr_code);
	switch (pcdr_code)
	{
		case 99 :
			ft_putstr_fd("0", 1);
			strlen += 1;
		break ;
		case 163 :
			ft_putstr_fd("C\0", 1);
			strlen += ft_strlen((char *)arg);
		break ;
		case 'p' :
			ft_putstr_fd(ft_itoa_base((long int)arg, "0123456789abcdef"), 1);
			
		break ;
		case 'd' :
			ft_putstr_fd(ft_itoa((long int)arg), 1);
			
		break ;
		case 'i' :
			ft_putstr_fd(ft_itoa((long int)arg), 1);
			
		break ;
		case 'u' :
			ft_putstr_fd(ft_itoa((unsigned long int)arg), 1);
			
		break ;
		case 'x' :
			ft_putstr_fd(ft_map_str(ft_itoa_base((long int)arg, "0123456789abcdef"), ft_tolower), 1);
			
		break ;
		case 'X' :
			ft_putstr_fd(ft_map_str(ft_itoa_base((long int)arg, "0123456789abcdef"), ft_toupper), 1);
			
		break ;
		case '%' :
			ft_putchar_fd('%', 1);
			strlen += 1;
		break ;
		default :
			strlen += 0;
		return (0);
	}
	return (offset);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	size_t	strlen;

	va_start(args, str);
	if (!va_arg(args, long))
	{
		ft_putstr_fd((char *)str, 1);
		return (ft_strlen((char *)str));
	}
	strlen = 0;
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			str += ft_pcdr_handle((char *)str, va_arg(args, void*), &strlen);
			continue;
		}
		ft_putchar_fd(*str++, 1);
		strlen++;
	}
	va_end(args);
	return (strlen);
}
