/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_digits.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 14:19:57 by epinaud           #+#    #+#             */
/*   Updated: 2024/08/22 16:10:03 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_count_digits(char *str)
{
	size_t	dcount;

	if (!str)
		return (0);
	dcount = 0;
	while (*str)
	{
		if (ft_isdigit(*str))
			dcount++;
		str++;
	}
	return (dcount);
}
