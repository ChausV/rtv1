/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 17:37:07 by vchaus            #+#    #+#             */
/*   Updated: 2017/11/08 17:37:08 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char *tdst;
	unsigned char *tsrc;

	tdst = (unsigned char*)dst;
	tsrc = (unsigned char*)src;
	if (tdst == NULL && tsrc == NULL)
		return (NULL);
	while (n > 0)
	{
		*(tdst + (n - 1)) = *(tsrc + (n - 1));
		n--;
	}
	return (dst);
}
