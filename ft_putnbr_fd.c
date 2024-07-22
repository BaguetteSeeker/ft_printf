/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:47:14 by epinaud           #+#    #+#             */
/*   Updated: 2024/07/23 01:37:23 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_fd(long int n, int fd, ...)
{
	va_list	leave_sign;
	
	va_start(leave_sign, fd);
	if (n < 0 && !va_arg(leave_sign, int))
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
	va_end(leave_sign);
}
