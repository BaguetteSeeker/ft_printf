/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_directives.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 21:22:55 by epinaud           #+#    #+#             */
/*   Updated: 2024/07/20 03:26:30 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

static t_directives	ft_set_type(const char *str, t_directives dirs)
{
	while (ft_strchr("cspuidxX%", *str))
	{
		dirs.spec = (dirs.spec * 10) + *str;
		str++;
	}

	return (dirs);
}

t_directives	ft_parse_directives(const char *str, va_list args, t_directives dirs)
{
	while (*str && ft_strchr("-0.*# +", *str))
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
		else if (*str == '*')
			dirs.width = va_arg(args, int);			
		else if (*str == '.' && str[1] == '*')
			dirs.precision = va_arg(args, int);
		else if (*str >= '0' && *str <= '9' && !dirs.precision)
			dirs.width = (dirs.width * 10) + (*str - '0');
		else if (*str >= '0' && *str <= '9' && dirs.precision)
			dirs.precision = (dirs.precision * 10) + (*str - '0');
		dirs.offset++;
		if (ft_strchr("cspuidxX%", *str++))
			return (ft_set_type(str, dirs));
	}
	return (dirs);
}
