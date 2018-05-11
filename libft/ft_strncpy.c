/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 18:05:43 by vchaus            #+#    #+#             */
/*   Updated: 2017/11/13 18:05:45 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	slen;

	slen = ft_strlen(src);
	ft_memcpy((void*)dst, (void*)src, sizeof(char) * len);
	if (slen < len)
		ft_bzero(dst + (slen + 1), len - (slen + 1));
	return (dst);
}
