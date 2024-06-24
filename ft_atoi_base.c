/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:54:43 by epinaud           #+#    #+#             */
/*   Updated: 2024/06/18 02:51:15 by epinaud          ###   ########.fr       */
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

static int	ft_base_integrity(char *base, int len)
{
	int	i;

	i = 0;
	if (base[0] == '\0' || base[1] == '\0' || ft_check_dup(base) == 1)
		return (0);
	while (i != len)
	{
		if (base[i] == '+' || base[i] == '-')
			return (0);
		i++;
	}
	return (1);
}

int	allowed_char(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	else if (c == '+' || c == '-')
		return (1);
	else
		return (0);
}

int	get_pos(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i] != c && base[i] != '\0')
		i++;
	if (base[i] == '\0')
		i = -1;
	return (i);
}

int	ft_atoi_base(char *str, char *base)
{
	int	i;
	int	blen;
	int	sum;
	int	sign;

	blen = 0;
	while (base[blen] != '\0')
		blen++;
	if (ft_base_integrity(base, blen) != 1)
		return (0);
	i = 0;
	sum = 0;
	sign = 1;
	while (allowed_char(str[i]))
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (ft_strchr(base, str[i]))
	{
		sum = sum * blen + (ft_strchr(base, str[i]) - base);
		i++;
	}
	return (sum *= sign);
}

/*int	main(void)
{
	char nbr[] = " ---+-+04d2";
	char *base = "0123456789ABCDEF";
	printf("Decoded numbers are : %d", ft_atoi_base(nbr, base));
}*/
