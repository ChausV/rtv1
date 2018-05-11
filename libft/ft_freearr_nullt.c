/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freearr_nullt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 17:55:30 by vchaus            #+#    #+#             */
/*   Updated: 2017/12/06 17:55:31 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_freearr_nullt(void **arr)
{
	void	**beg;

	beg = arr;
	if (arr == NULL)
		return ;
	while (*arr != NULL)
	{
		free(*(arr));
		*(arr++) = NULL;
	}
	free(*(arr));
	*(arr) = NULL;
	free(beg);
	beg = NULL;
}
