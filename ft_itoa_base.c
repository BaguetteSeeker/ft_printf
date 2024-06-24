/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:54:43 by epinaud           #+#    #+#             */
/*   Updated: 2024/06/24 16:08:39 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_dup(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (str[i] != '\0')
	{
		j = i + 1;
		while (str[j] != '\0')
		{
			if (str[i] == str[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	ft_allowed_char(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	else if (c == '+' || c == '-')
		return (1);
	else
		return (0);
}

static int	ft_base_integrity(char *base)
{
	if (!*base || !*base + 1 || ft_check_dup(base))
		return (0);
	while (*base)
	{
		if (ft_allowed_char(*base))
			return (0);
		base++;
	}
	return (1);
}

static size_t	ft_count_digits(long int n)
{
	size_t	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		count++;
	}
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa_base(int n, char *base)
{
	long int	lnum;
	size_t		count;
	char		*str;

	lnum = n;
	count = ft_count_digits(n);
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
