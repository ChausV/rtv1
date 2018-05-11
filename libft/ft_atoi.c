/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 19:13:32 by vchaus            #+#    #+#             */
/*   Updated: 2017/12/06 19:13:33 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	long long int	res;
	int				sign;
	char			*s;

	res = 0;
	sign = 1;
	s = (char*)str;
	while (*s == 9 || *s == 10 || *s == 11 || *s == 12 || *s == 13 || *s == 32)
		s++;
	if (*s == '+')
		s++;
	else if (*s == '-')
	{
		sign = -1;
		s++;
	}
	while (*s && ft_isdigit(*s))
	{
		if ((res * 10) + (*(s) - 48) < res && sign == 1)
			return (-1);
		if ((res * 10) + (*(s) - 48) < res && sign == -1)
			return (0);
		res = (res * 10) + (*(s++) - 48);
	}
	return ((res * sign));
}
