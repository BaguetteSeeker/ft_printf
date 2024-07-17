/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_directives.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 21:22:55 by epinaud           #+#    #+#             */
/*   Updated: 2024/07/17 21:27:00 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_isdirective(int c)
{
	return (ft_strchr("-0.*# +", c));
}

static t_directives	ft_init_directives(t_directives dirs)
{
	dirs.spec = 0;
	dirs.width = 0;
	dirs.left = 0;
	dirs.zero = 0;
	dirs.star = 0;
	dirs.precision = -1;
	dirs.hash = 0;
	dirs.space = 0;
	dirs.plus = 0;
	return (dirs);
}

t_directives	ft_parse_directives(const char *str, va_list *args, t_directives dirs)
{
	while (*str && ft_strchr("-0.*# +", *str))
	{
		if (*str == '-')
			ft_flag_left(dirs);
		else if (*str == '#')
			dirs.hash = 1;
		else if (*str == ' ')
			dirs.space = 1;
		else if (*str == '+')
			dirs.plus = 1;
		else if (*str == '0' && dirs.left == 0 && dirs.width == 0)
			dirs.zero = 1;
		else if (*str == '.')
			dirs.offset = ft_flag_precision(*str, dirs.offset, *args, dirs);
		else if (*str == '*')
			ft_flag_width(*args, dirs);
		else if (ft_isdigit(*str))
			ft_flag_digit(*str, dirs);
		else if (ft_istype(*str))
		{
			dirs.spec = *str;
			break ;
		}
	}
	return (dirs);
}
