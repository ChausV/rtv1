/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inverse_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 14:55:29 by vchaus            #+#    #+#             */
/*   Updated: 2018/05/21 14:55:40 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"



// int		non_zero_pivot(double m[4][4])
// {
// 	int		i;
// 	int		j;
// 	double	max;

// 	i = 0;
// 	while(i < 4)
// 	{
// 		if (m[i][i] == 0.0)
// 		{
// 			j = 0;
// 			max = 0.0;
// 			while(j < 4)
// 			{
// 				if (fabs(m[j][i]) > )
// 			}
// 		}
// 		i++;
// 	}
// 	return (0);
// }

int		is_zero_pivot(double m[4][4])
{
	int		i;

	i = 0;
	while(i < 4)
	{
		if (m[i][i] == 0.0)
			return (i);
		i++;
	}
	return (-1);
}

void	swap_matr_line(double tmp[4][4], int a, int b, double to_o[4][4])
{
	int		i;
	double	temp;

	i = 0;
	while(i < 4)
	{
		temp = tmp[a][i];
		tmp[a][i] = tmp[b][i];
		tmp[b][i] = temp;
		temp = to_o[a][i];
		to_o[a][i] = to_o[b][i];
		to_o[b][i] = temp;
		i++;
	}
}

void	non_zero_pivot(double tmp[4][4], double to_o[4][4])
{
	int		zero_i;
	int		i;
	int		targ_i;
	double	max;

	while((zero_i = is_zero_pivot(tmp)) != -1)
	{
		i = 0;
		max = 0.0;
		while(i < 4)
		{
			if (fabs(tmp[i][zero_i]) > max)
			{
				max = fabs(tmp[i][zero_i]);
				targ_i = i;
			}
			i++;
		}
		if (max == 0.0)
			ft_putendl("____singular matrix____");
		else
			swap_matr_line(tmp, zero_i, targ_i, to_o);
	}
}

int		matrix_inverse(double to_o[4][4], double to_w[4][4])
{
	double	tmp[4][4];

	if (matr_determ(to_w) == 0.0)
		return (-1);
	matr_copy(tmp, to_w);
	non_zero_pivot(tmp, to_o);





	put_matr(tmp);
	ft_putendl("");
	put_matr(to_o);
	return (0);
}









