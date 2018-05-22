/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation_functions.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 11:40:21 by vchaus            #+#    #+#             */
/*   Updated: 2018/05/14 11:40:22 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

t_point		point_mult_matr(t_point *p, double m[4][4])
{
	t_point	res;
	double	w;

	res.x = p->x * m[0][0] + p->y * m[1][0] + p->z * m[2][0] + m[3][0];
	res.y = p->x * m[0][1] + p->y * m[1][1] + p->z * m[2][1] + m[3][1];
	res.z = p->x * m[0][2] + p->y * m[1][2] + p->z * m[2][2] + m[3][2];
	w = p->x * m[0][3] + p->y * m[1][3] + p->z * m[2][3] + m[3][3];
	if (w != 1.0 && w != 0.0)
	{
		res.x /= w;
		res.y /= w;
		res.z /= w;
	}
	return (res);
}

t_vector	vect_mult_matr(t_vector *v, double m[4][4])
{
	t_vector	res;

	res.x = v->x * m[0][0] + v->y * m[1][0] + v->z * m[2][0];
	res.y = v->x * m[0][1] + v->y * m[1][1] + v->z * m[2][1];
	res.z = v->x * m[0][2] + v->y * m[1][2] + v->z * m[2][2];
	return (res);
}

t_vector	normal_mult_tr_matr(t_vector *v, double m[4][4])
{
	t_vector	res;

	res.x = v->x * m[0][0] + v->y * m[0][1] + v->z * m[0][2];
	res.y = v->x * m[1][0] + v->y * m[1][1] + v->z * m[1][2];
	res.z = v->x * m[2][0] + v->y * m[2][1] + v->z * m[2][2];
	return (res);
}
