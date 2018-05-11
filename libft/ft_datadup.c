/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_datadup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 16:28:08 by vchaus            #+#    #+#             */
/*   Updated: 2017/12/10 16:28:11 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_datadup(const void *start, size_t size)
{
	void	*res;

	if (!start)
		return (NULL);
	res = malloc(size);
	if (!res)
		return (NULL);
	ft_memmove(res, start, size);
	return (res);
}
