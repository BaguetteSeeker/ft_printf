/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsetype.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:48:30 by epinaud           #+#    #+#             */
/*   Updated: 2024/06/24 20:13:41 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	vtoint(void *argptr)
{
	int	*param;
	
	param = argptr;
	ft_putnbr_fd(*param, 1);
	return (*param);
}

static char	vtochar(void *argptr)
{
	char	*param;

	param = argptr;
	ft_putchar_fd(*param, 1);
	return (*param);
}

static char	*vtocharptr(void *argptr)
{
	char *param;

	param = argptr;
	ft_putstr_fd(param, 1);
	return (param);
}

int	parsetype(int type, void *argptr)
{
	if (type == 110)
		return ft_nbrlen(vtoint(argptr));
	else if (type == 99)
		return vtochar(argptr);
	else if (type == 115)
		return ft_strlen(vtocharptr(argptr));
	else
		return (0);
}
