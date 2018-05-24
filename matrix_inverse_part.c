/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_inverse_part.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 17:52:46 by vchaus            #+#    #+#             */
/*   Updated: 2018/05/23 17:52:46 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

static void	columns_to_zero_part(double tmp[4][4], double to_o[4][4], int i,
																		int j)
{
	int		l;
	double	k;

	l = 0;
	if ((k = tmp[j][i] / tmp[i][i]) != 0.0)
	{
		while (l < 4)
		{
			tmp[j][l] -= k * tmp[i][l];
			to_o[j][l] -= k * to_o[i][l];
			l++;
		}
		l = 0;
		tmp[j][i] = 0.0;
	}
}

void		columns_to_zero(double tmp[4][4], double to_o[4][4])
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < 4)
	{
		while (j < 4)
		{
			if (i != j)
			{
				columns_to_zero_part(tmp, to_o, i, j);
			}
			j++;
		}
		j = 0;
		i++;
	}
}
