/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_directives.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 21:22:55 by epinaud           #+#    #+#             */
/*   Updated: 2024/07/17 00:18:58 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_isdirective(int c)
{
	return (ft_strchr("-0.*# +", c));
}

t_directives	ft_parse_directives(const char *str, va_list *args)
{
	t_directives	directives;

	while (*str && ft_isflag(*str))
	{
		if (*str == '-')
			ft_flag_left(directives);
		else if (*str == '#')
			directives.hash = 1;
		else if (*str == ' ')
			directives.space = 1;
		else if (*str == '+')
			directives.plus = 1;
		else if (*str == '0' && directives.left == 0 && directives.width == 0)
			directives.zero = 1;
		else if (*str == '.')
			directives.offset = ft_flag_precision(*str, directives.offset, *args, directives);
		else if (*str == '*')
			ft_flag_width(*args, directives);
		else if (ft_isdigit(*str))
			ft_flag_digit(*str, directives);
		else if (ft_istype(*str))
		{
			directives.spec = *str;
			break ;
		}
	}
	return (directives);
}
