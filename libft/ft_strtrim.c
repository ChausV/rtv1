/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 15:16:07 by vchaus            #+#    #+#             */
/*   Updated: 2017/12/04 15:16:07 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	count;
	char	*itr;
	char	*stop;

	if (s == NULL)
		return (NULL);
	if ((count = ft_strlen(s)) == 0)
		return (ft_strnew(0));
	itr = (char*)(s + count - 1);
	while ((*itr == ' ' || *itr == '\n' || *itr == '\t') && (itr != s))
	{
		count--;
		itr--;
	}
	stop = itr + 1;
	itr = (char*)s;
	while ((*itr == ' ' || *itr == '\n' || *itr == '\t') && (itr != stop))
	{
		count--;
		itr++;
	}
	return (ft_strsub(itr, 0, count));
}
