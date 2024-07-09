/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:54:43 by epinaud           #+#    #+#             */
/*   Updated: 2024/07/05 18:59:47 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_base_integrity(char *base)
{
	int	i;

	i = 0;
	if (base[0] == '\0' || base[1] == '\0' || ft_check_dup(base) == 1)
		return (0);
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-')
			return (0);
		i++;
	}
	return (1);
}

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
