/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 14:37:57 by vchaus            #+#    #+#             */
/*   Updated: 2017/11/15 14:38:56 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	ch;
	size_t	len;
	char	*str;

	ch = (char)c;
	len = ft_strlen(s) + 1;
	str = (char*)s;
	while (len > 0)
	{
		len--;
		if (*(str + len) == ch)
			return (str + len);
	}
	return (NULL);
}
