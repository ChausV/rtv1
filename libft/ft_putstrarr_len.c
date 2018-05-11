/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrarr_len.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 15:49:39 by vchaus            #+#    #+#             */
/*   Updated: 2017/12/11 15:49:40 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstrarr_len(char **arr, char *delim, size_t len)
{
	if (arr == NULL || delim == NULL)
		return ;
	while (len > 0)
	{
		ft_putstr(*(arr++));
		if (len-- != 1)
			ft_putstr(delim);
	}
}
