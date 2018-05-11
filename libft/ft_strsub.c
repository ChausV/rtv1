/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 18:58:13 by vchaus            #+#    #+#             */
/*   Updated: 2017/12/01 18:58:15 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*res;

	res = ft_strnew(len);
	if (res == NULL || s == NULL)
		return (NULL);
	return ((char*)ft_memcpy(res, s + start, len * sizeof(char)));
}
