/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 20:45:52 by epinaud           #+#    #+#             */
/*   Updated: 2024/06/06 21:21:57 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *s)
{
	char	*sptr;
	int		len;
	int		i;

	len = ft_strlen(s) + 1;
	sptr = malloc(sizeof(char) * len);
	if (sptr == NULL)
		exit(0);
	i = 0;
	while (i < (len))
	{
		sptr[i] = s[i];
		i++;
	}
	return (sptr);
}
