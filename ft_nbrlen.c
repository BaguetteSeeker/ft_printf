/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 01:19:34 by epinaud           #+#    #+#             */
/*   Updated: 2024/06/22 01:28:28 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_nbrlen(long int nbr)
{
	size_t	count;

	count = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
		count++;
	while (nbr > 0)
	{
		nbr /= 10;
		count++;
	}
	return (count);
}
