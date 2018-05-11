/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 20:07:55 by vchaus            #+#    #+#             */
/*   Updated: 2017/12/04 20:07:55 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_arr_elements_for_split(char *s, size_t count, char **res, char c)
{
	size_t	count2;
	size_t	i;

	i = 0;
	while (i < count)
	{
		while (*s == c)
			s++;
		if (ft_strchr(s, c) == NULL)
			count2 = ft_strchr(s, '\0') - s;
		else
			count2 = ft_strchr(s, c) - s;
		*(res + i++) = ft_strsub(s, 0, count2);
		if (*(res + i - 1) == NULL)
		{
			ft_freearr_nullt((void**)res);
			return (1);
		}
		s += count2;
	}
	return (0);
}

char		**ft_strsplit(char const *s, char c)
{
	size_t	count;
	char	*siter;
	char	**res;

	if (s == NULL)
		return (NULL);
	count = 0;
	siter = (char*)s;
	while (*siter != '\0')
	{
		if (*siter != c && (*(siter + 1) == c || *(siter + 1) == '\0'))
			count++;
		siter++;
	}
	if ((res = (char**)ft_memalloc((count + 1) * sizeof(char*))) == NULL)
		return (NULL);
	if (count == 0)
		return (res);
	if (ft_arr_elements_for_split((char*)s, count, res, c) == 1)
		return (NULL);
	return (res);
}
