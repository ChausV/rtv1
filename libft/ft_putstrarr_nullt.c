/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrarr_nullt.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 16:21:08 by vchaus            #+#    #+#             */
/*   Updated: 2017/12/06 16:21:08 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstrarr_nullt(char **arr, char *delim)
{
	if (arr == NULL || delim == NULL)
		return ;
	while (*arr != NULL)
	{
		ft_putstr(*(arr++));
		if (*(arr) != NULL)
			ft_putstr(delim);
	}
}
