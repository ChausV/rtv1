/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 21:47:06 by vchaus            #+#    #+#             */
/*   Updated: 2017/12/06 21:47:07 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_fill_res_for_itoa(char *res, char *resiter, long int num)
{
	while (1)
	{
		*resiter = (num % 10) + 48;
		num /= 10;
		if (resiter == res || *(resiter - 1) == '-')
			return ;
		else
			resiter--;
	}
}

char		*ft_itoa(int n)
{
	long int	num;
	char		*res;
	char		*resiter;

	num = (long int)n;
	if (num < 0)
	{
		num *= -1;
		if ((res = ft_strnew(ft_digcount(num) + 1)) == NULL)
			return (NULL);
		resiter = res;
		*(resiter++) = '-';
	}
	else
	{
		if ((res = ft_strnew(ft_digcount(num))) == NULL)
			return (NULL);
		resiter = res;
	}
	resiter += ft_digcount(num) - 1;
	ft_fill_res_for_itoa(res, resiter, num);
	return (res);
}
