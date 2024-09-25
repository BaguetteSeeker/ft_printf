/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:54:43 by epinaud           #+#    #+#             */
/*   Updated: 2024/09/12 21:44:49 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*fill_str(char *dest, long int nbr, size_t *siz, size_t baselen)
{
	while (nbr > 0)
	{
		dest[*siz--] = nbr % baselen + 48;
		nbr /= baselen;
	}
	return (dest);
}

char	*ft_itoa_base(long int n, char *base, ...)
{
	char		*str;
	size_t		strsiz;
	size_t		baselen;
	va_list		no_sign;

	baselen = ft_strlen(base);
	strsiz = ft_nbrblen(n, baselen);
	str = malloc((strsiz + 1) * sizeof(char));
	if (!str || !ft_base_integrity(base))
		return (NULL);
	str[strsiz--] = '\0';
	if (n == 0)
		str[0] = '0';
	va_start(no_sign, base);
	if (n < 0 && !va_arg(no_sign, int))
	{
		str[0] = '-';
		n = -n;
	}
	va_end(no_sign);
	return (fill_str(str, n, &strsiz, baselen));
}
