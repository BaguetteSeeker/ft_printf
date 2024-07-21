/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_directives.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 21:22:55 by epinaud           #+#    #+#             */
/*   Updated: 2024/07/21 20:40:20 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_directives	ft_init_directives(t_directives dirs)
{
	dirs.spec = 0;
	dirs.width = 0;
	dirs.left = 0;
	dirs.zero = 0;
	dirs.star = 0;
	dirs.precision = 0;
	dirs.hash = 0;
	dirs.space = 0;
	dirs.plus = 0;
	dirs.offset = 0;
	return (dirs);
}

static t_directives	ft_parse_flags(const char *str, t_directives dirs)
{
	if (*str == '-')
		dirs.left = '1';
	else if (*str == '#')
		dirs.hash = 1;
	else if (*str == ' ')
		dirs.space = 1;
	else if (*str == '+')
		dirs.plus = 1;
	else if (*str == '0' && dirs.width == 0)
		dirs.zero = 1;
	return (dirs);
}

void	ft_print_dirs(t_directives dirs)
{
	if (dirs.zero && !dirs.left)
		ft_putchar_fd('\0', 1);
	/*
	if (dirs.plus && val > 0)
		ft_putchar('+');

	if (dirs.space && !dirs.left && !dirs.plus)
		print minus for neg or 1 space for pos num 

	if (dirs.hash && ft_strchr("xX", dirs.type))
	{
		ft_putchr('0');
		ft_putchar(dirs.type);
	}

	//pad width print_width
	if (dirs.width > str/nbrlen(arg) && !dirs.left && !dirs.precision)
		if (dirs.zero)
			chr = '0';
		else
			chr = ' ';
		l4n = ft_atoi(*str);
		while(len)
		{
			ft_putchar(char);
		}
	*/
	//check
}
/*static t_directives	ft_set_type(const char *str, t_directives dirs)
{
	while (ft_strchr("cspuidxX%", *str))
	{
		dirs.spec = (dirs.spec * 10) + *str;
		str++;
	}

	return (dirs);
}*/

static int	ft_parse_len(const char *str, va_list args, int offset, int *ldest)
{
	if (str[offset] == '*')
	{
		offset++;
		*ldest = va_arg(args, int);
	}
	else
		while (ft_isdigit(str[offset]))
			*ldest = (*ldest * 10) + (str[offset++] - '0');
	return (offset);
}

t_directives	ft_parse_dirs(const char *str, va_list args, t_directives dirs)
{
	while (ft_strchr("-#+ 0", str[dirs.offset]))
		dirs = ft_parse_flags(&str[dirs.offset++], dirs);
	dirs.offset += ft_parse_len(str, args, dirs.offset, &dirs.width);
	if (str[dirs.offset] == '.' )
	{	
		dirs.offset++;
		dirs.offset += ft_parse_len(str, args, dirs.offset, &dirs.precision);
	}
	//while (ft_strchr("cspuidxX%", str[dirs.offset++]))
		//dirs = ft_parse_spec();
	return (dirs);
}
