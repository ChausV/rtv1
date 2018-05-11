/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 17:04:15 by vchaus            #+#    #+#             */
/*   Updated: 2017/11/15 17:04:16 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*res;
	char	*result;

	if (s == NULL || f == NULL)
		return (NULL);
	res = ft_strdup(s);
	if (res == NULL)
		return (NULL);
	result = res;
	while (*res != '\0')
	{
		*res = f(*res);
		res++;
	}
	return (result);
}
