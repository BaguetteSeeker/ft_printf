/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:02:09 by epinaud           #+#    #+#             */
/*   Updated: 2024/08/09 14:04:34 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_putnbr_base_fd(unsigned long n, char *base, int fd)
{
	size_t	blen;
	size_t	nlen;

	if (ft_base_integrity(base))
		return (0);
	blen = ft_strlen(base);
	nlen = 0;
	if (n >= blen)
		nlen = ft_putnbr_base_fd(n / blen, base, fd);
	ft_putchar_fd(base[n % blen], fd);
	nlen++;
	return (nlen);
}
