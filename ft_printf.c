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

/* static char	*ft_map_str(char *str, int (*f)(int))
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

static int	ft_parse_pcdr(char *pcdr_start)
{
	size_t	offset;

	while (*pcdr_start != ' ' && *pcdr_start)
	{
		pcdr_start++;
		offset++;
	}
	return (offset);
} */

static int	ft_pcdr_handle(char *pcdr, va_list *arg, size_t *strlen, va_list *argcpy)
{
	char	*paramset;
	int		pcdr_code;
	size_t	offset;

	paramset = "cspdiuxX%";
	pcdr_code = 0;
	offset = 0;
	while (pcdr[offset] != ' ' && pcdr[offset] != '\0')
			pcdr_code = pcdr_code * 10 + pcdr[offset++];
	//printf("PCDR CODE IS : %d \n", pcdr_code);
	return ft_printtype_caller(pcdr_code, va_arg(*arg, long long *));







	
	/*switch (pcdr_code)
	{
		//c
		case 99 :
			//printf("CHAR TO PRINT IS : %c \n", va_arg(*argcpy, int));
			ft_putchar_fd(va_arg(*arg, int), 1);
			*strlen += 1;
			va_arg(*argcpy, int);
		break ;
		//s
		case 115 :
			//printf("CHAR TO PRINT IS : %s \n", va_arg(*argcpy, char*));
			ft_putstr_fd(va_arg(*arg, char*), 1);
			*strlen += ft_strlen(va_arg(*argcpy, char*));
		break ;
		//p
		case 112 :
			return ft_printtype_caller(112, va_arg(*arg, long long *));
			//*strlen += ft_strlen(va_arg(*argcpy, char*));
			
		break ;
		//d
		case 100 :
			return ft_printtype_caller(100, va_arg(*arg, long long *));
			
		break ;
		case 105 :
			return ft_printtype_caller(105, va_arg(*arg, long long *));
			
		break ;
		case 'u' :
			//ft_putstr_fd(ft_itoa((unsigned long int)arg), 1);
			
		break ;
		case 'x' :
			//ft_putstr_fd(ft_map_str(ft_itoa_base((long int)arg, "0123456789abcdef"), ft_tolower), 1);
			
		break ;
		case 'X' :
			//ft_putstr_fd(ft_map_str(ft_itoa_base((long int)arg, "0123456789abcdef"), ft_toupper), 1);
			
		break ;
		case 37 :
			ft_putchar_fd('%', 1);
			strlen += 1;
		break ;
		default :
			strlen += 0;
		return (0);
	}*/
	return (offset);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	va_list	argcpy;
	size_t	strlen;

	if (!str)
		return (0);
	va_start(args, str);
	va_copy(argcpy, args);
	/*if (!va_arg(args, long))
	{
		ft_putstr_fd((char *)str, 1);
		return (ft_strlen((char *)str));
	}*/
	strlen = 0;
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			str += ft_pcdr_handle((char *)str, &args, &strlen, &argcpy);
			continue;
		}
		ft_putchar_fd(*str++, 1);
		strlen++;
	}
	va_end(args);
	va_end(argcpy);
	//printf("Strlen is %zu \n", strlen);
	return (strlen);
}
