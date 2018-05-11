/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 14:26:57 by vchaus            #+#    #+#             */
/*   Updated: 2017/11/09 14:26:58 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char *d;
	unsigned char *s;

	d = (unsigned char*)dst;
	s = (unsigned char*)src;
	if (s == NULL && d == NULL)
		return (NULL);
	if ((d - s) <= 0)
	{
		while (len-- > 0)
		{
			*d++ = *s++;
		}
	}
	else
	{
		while (len-- > 0)
		{
			*(d + len) = *(s + len);
		}
	}
	return (dst);
}
