/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:05:27 by epinaud           #+#    #+#             */
/*   Updated: 2024/07/25 10:01:32 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

char	*ft_itoa(int n)
{
	long int	lnum;
	size_t		count;
	char		*str;

	lnum = n;
	count = ft_count_digits(n);
	str = malloc((count + 1) * sizeof(char));
	if (!str)
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
		str[count] = lnum % 10 + '0';
		count--;
		lnum /= 10;
	}
	return (str);
}
