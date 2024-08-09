/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:47:14 by epinaud           #+#    #+#             */
/*   Updated: 2024/08/09 03:25:57 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_fd(long int n, int fd, ...)
{
	va_list	no_sign;
	
	va_start(no_sign, fd);
	if (n < 0 && !va_arg(no_sign, int))
		ft_putchar_fd('-', 1);
	if (n == 2147483648)
		ft_putstr_fd("2147483648", fd);
	else
	{
		if (n < 0)
			n = -n;
		if (n > 9)
			ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd(n % 10 + 48, fd);
	}
	va_end(no_sign);
}
