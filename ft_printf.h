/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:06:08 by epinaud           #+#    #+#             */
/*   Updated: 2024/06/18 16:43:01 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <limits.h>
# include "libft.h"

//Mandatory
int	ft_printf(const char *str, ...);
int	ft_print_type_router(int type, long long argptr);
int	ft_base_integrity(char *base);
int	ft_check_dup(char *str);

//Bonus

typedef struct s_directives
{
	int	spec;
	int	width;
	int	left;
	int	zero;
	int	star;
	int	precision;
	int	hash;
	int	space;
	int	plus;
    int offset;
}		t_directives;

t_directives    ft_parse_directives(const char *str, va_list *args);

#endif
