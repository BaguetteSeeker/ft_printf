/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:54:43 by epinaud           #+#    #+#             */
/*   Updated: 2024/07/10 14:31:11 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_itoa_base(long int n, char *base)
{
	long int	lnum;
	size_t		count;
	char		*str;

	lnum = n;
	count = ft_nbrlen(n);
	str = malloc((count + 1) * sizeof(char));
	if (!str || !ft_base_integrity(base))
		return (NULL);
	str[count--] = '\0';
	if (lnum == 0)
		str[0] = '0';
	if (lnum < 0)
	{
		str[0] = '-';
		lnum = -lnum;
	}
	while (lnum > 0)
	{
		str[count] = lnum % ft_strlen(base) + 48;
		count--;
		lnum /= ft_strlen(base);
	}
	return (str);
}

/*int	main(void)
{
	int nbr = -2147483648;
	char *base = "0123456789ABCDEF";
	printf("Decoded numbers are : %s", ft_itoa_base(nbr, base));
}*/
