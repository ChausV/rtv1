/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 18:17:51 by vchaus            #+#    #+#             */
/*   Updated: 2017/11/30 18:17:53 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	if (*needle == '\0')
		return ((char*)haystack);
	i = 0;
	if (len >= ft_strlen(haystack))
		return (ft_strstr(haystack, needle));
	else if (len >= ft_strlen(needle))
	{
		while (i <= len - ft_strlen(needle))
		{
			if (*(haystack + i) == *needle)
			{
				if (ft_strncmp(haystack + i, needle, ft_strlen(needle)) == 0)
					return ((char*)(haystack + i));
			}
			i++;
		}
	}
	return (NULL);
}
