/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 14:18:42 by vchaus            #+#    #+#             */
/*   Updated: 2017/11/15 14:18:46 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	ch;
	size_t	len;
	size_t	i;
	char	*str;

	ch = (char)c;
	len = ft_strlen(s) + 1;
	i = 0;
	str = (char*)s;
	while (len > i)
	{
		if (*(str + i) == ch)
			return (str + i);
		else
			i++;
	}
	return (NULL);
}
