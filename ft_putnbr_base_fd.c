/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:02:09 by epinaud           #+#    #+#             */
/*   Updated: 2024/06/26 15:12:11 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_base_fd(int n, char *base, int fd)
{
	int	blen;
	printf("Base is %s \n", base);
	blen = ft_strlen(base);
	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else
	{
		if (n < 0)
		{
			ft_putchar_fd('-', fd);
			n = -n;
		}
		if (n > blen)
			ft_putnbr_base_fd(n / blen, base, fd);
		ft_putchar_fd(base[n % blen], fd);
	}
}
