/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 17:17:13 by vchaus            #+#    #+#             */
/*   Updated: 2018/04/24 17:17:14 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

double	vector_length(t_vector *vector)
{
	return (sqrt(vector->x * vector->x + vector->y * vector->y +
														vector->z * vector->z));
}

void	vector_normalize(t_vector *v, t_vector *v_res)
{
	double sq_len;
	double inv_len;

	sq_len = v->x * v->x + v->y * v->y + v->z * v->z;
	if (sq_len > 0)
	{
		inv_len = 1.0 / sqrt(sq_len);
		v_res->x = v->x * inv_len;
		v_res->y = v->y * inv_len;
		v_res->z = v->z * inv_len;
	}
}

double	vector_dot_prod(t_vector *vect_1, t_vector *vect_2)
{
	return (vect_1->x * vect_2->x + vect_1->y * vect_2->y +
														vect_1->z * vect_2->z);
}

double	vector_dot_point(t_vector *vect, t_point *p)
{
	return (vect->x * p->x + vect->y * p->y + vect->z * p->z);
}

void	vector_cross_prod(t_vector *vect_1, t_vector *vect_2, t_vector *res)
{
	res->x = vect_1->y * vect_2->z - vect_1->z * vect_2->y;
	res->y = vect_1->z * vect_2->x - vect_1->x * vect_2->z;
	res->z = vect_1->x * vect_2->y - vect_1->y * vect_2->x;
}
