/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 17:50:01 by vchaus            #+#    #+#             */
/*   Updated: 2017/11/15 17:50:01 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*res;
	unsigned int	i;

	if (s == NULL || f == NULL)
		return (NULL);
	i = 0;
	res = ft_strdup(s);
	if (res == NULL)
		return (NULL);
	while (res[i] != '\0')
	{
		res[i] = f(i, res[i]);
		i++;
	}
	return (res);
}
