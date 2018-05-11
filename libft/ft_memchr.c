/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:30:42 by vchaus            #+#    #+#             */
/*   Updated: 2017/11/09 17:30:43 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *st;
	unsigned char ch;

	st = (unsigned char*)s;
	ch = (unsigned char)c;
	while (n-- > 0)
	{
		if (*st == ch)
			return (st);
		else
			st++;
	}
	return (NULL);
}
