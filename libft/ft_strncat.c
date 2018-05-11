/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 15:46:24 by vchaus            #+#    #+#             */
/*   Updated: 2017/11/14 15:46:25 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t	len;

	len = ft_strlen(s1);
	if (n > ft_strlen(s2))
		n = ft_strlen(s2);
	ft_memcpy(s1 + len, s2, n * sizeof(char));
	*(s1 + len + (n * sizeof(char))) = '\0';
	return (s1);
}
