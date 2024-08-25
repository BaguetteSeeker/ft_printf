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

//Bonus
typedef struct s_directives
{
	int	type;
	int	width;
	int	left;
	int	zero;
	int	star;
	int	precision;
	int	hash;
	int	space;
	int	plus;
	int	offset;
	int	strlen;
	int	siglen;
	int	arglen;
	int	maxlen;
	int	ndigits;
	int	putnull;
	int	put_tail;
}		t_directives;

//Mandatory
int				ft_printf(const char *str, ...);
int				ft_print_arg(va_list *arg, t_directives dirs);
int				ft_base_integrity(char *base);
int				ft_check_dup(char *str);
t_directives	ft_init_directives(t_directives dirs);
t_directives	ft_parse_dirs(char *str, va_list *args, t_directives *dirs);
size_t			ft_print_directives(long long arg, t_directives dirs);
size_t			ft_parse_len(const char *str, va_list *args, int *ldest);

#endif
