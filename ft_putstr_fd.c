/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:36:30 by epinaud           #+#    #+#             */
/*   Updated: 2024/08/09 15:54:16 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
		ft_putchar_fd(*s++, fd);
}

void	ft_putstrcap_fd(char *s, size_t cap, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (*s && i < (int)cap)
	{
		ft_putchar_fd(*s++, fd);
		i++;
	}
}
