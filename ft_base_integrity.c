/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base_integrity.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:54:34 by epinaud           #+#    #+#             */
/*   Updated: 2024/07/10 13:51:37 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_base_integrity(char *base)
{
	if (!*base || !*base + 1 || ft_check_dup(base))
		return (0);
	while (*base)
	{
		if (ft_strchr("+- \t\n\v\f\r", *base))
			return (0);
		base++;
	}
	return (1);
}
