/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:02:09 by epinaud           #+#    #+#             */
/*   Updated: 2024/07/06 18:49:32 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_putnbr_base_fd(unsigned long long n, char *base, int fd)
{
	size_t	blen;
	size_t	nlen;

	if (ft_check_dup(base))
		return (0);
	blen = ft_strlen(base);
	nlen = 0;
	if ((long unsigned int)n > blen - 1)
		nlen = ft_putnbr_base_fd(n / blen, base, fd);
	ft_putchar_fd(base[n % blen], fd);
	nlen++;
	return (nlen);
}
