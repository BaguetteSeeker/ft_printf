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

static char	*ft_pcdr_handle(unsigned char pcdr, char *str, va_list args)
{
	char	*paramset;
	char	*converted_content;
	size_t	offset;

	paramset = "cspdiuxX%";
	switch (pcdr)
	{
		case 'c' :
			converted_content = va_arg(args, char *);
			offset = 1;
		break ;
		case 's' :
			converted_content = va_arg(args, char *);
			offset = 1;
		break ;
		case 'p' :
			converted_content = ft_itoa_base(va_arg(args, int), "0123456789abcdef");
			offset = 1;
		break ;
		case 'd' :
			converted_content = ft_itoa(va_arg(args, int));
			offset = 1;
		break ;
		case 'i' :
			converted_content = ft_itoa(va_arg(args, int));
			offset = 1;
		break ;
		case 'u' :
			converted_content = ft_itoa(va_arg(args, unsigned int));
			offset = 1;
		break ;
		case 'x' :
			converted_content = ft_map_str(ft_itoa_base(va_arg(args, int), "0123456789abcdef"), ft_tolower);
			offset = 1;
		break ;
		case 'X' :
			converted_content = ft_map_str(ft_itoa_base(va_arg(args, int), "0123456789abcdef"), ft_toupper);
			offset = 1;
		break ;
		case '%' :
			converted_content = ft_strdup("%");
			offset = 1;
		break ;
		default :
			converted_content = "\0";
			offset = 0;
		return (NULL);
	}
	return (ft_strjoin(converted_content, str += offset));
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		flag;
	size_t	strlen;
	char	*strtoprint;
	char	*prevstr;
	char	**chains;

	va_start(args, str);
	if (!va_arg(args, long))
	{
		ft_putstr_fd((char *)str, 1);
		return (ft_strlen((char *)str));
	}
	else
		chains = ft_split(str, '%');
	flag = 0;
	while (chains)
	{
		if (!flag)
		{
			strtoprint = *chains;
			flag = 1;
		}
		else
		{
			prevstr = strtoprint;
			strtoprint = ft_strjoin(prevstr, ft_pcdr_handle(**chains, *chains, args));
			free(prevstr);
			prevstr = NULL;
			if (!strtoprint)
				return (0);
		}
		chains++;
	}
	va_end(args);
	ft_putstr_fd(strtoprint, 1);
	strlen = ft_strlen(strtoprint);
	free(strtoprint);
	return (strlen);
}
