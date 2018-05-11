/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 12:55:07 by vchaus            #+#    #+#             */
/*   Updated: 2017/11/16 12:55:07 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char*)s1;
	str2 = (unsigned char*)s2;
	i = 1;
	if (n == 0)
		return (0);
	while (*str1 != '\0' && *str2 != '\0')
	{
		if ((*str1 != *str2) || (i == n))
			return (*str1 - *str2);
		else
		{
			str1++;
			str2++;
			i++;
		}
	}
	if (*str1 != *str2)
		return (*str1 - *str2);
	return (0);
}
