/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base_sanitation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:54:34 by epinaud           #+#    #+#             */
/*   Updated: 2024/07/09 21:43:13 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

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
