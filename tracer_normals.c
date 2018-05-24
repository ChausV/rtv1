/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer_normals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 13:46:15 by vchaus            #+#    #+#             */
/*   Updated: 2018/05/24 13:46:15 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

static t_vector	get_cylinder_normal(t_point *p, t_object *cylinder)
{
	t_point		op;
	t_vector	on;
	t_vector	res;

	op = point_mult_matr(p, cylinder->to_o);
	on = vector_from_points(&op, &(t_point){0.0, op.y, 0.0});
	res = normal_mult_tr_matr(&on, cylinder->to_o);
	return (res);
}

static t_vector	get_cone_normal(t_point *p, t_object *cone)
{
	t_point		op;
	t_vector	on;
	t_vector	res;
	double		d;

	op = point_mult_matr(p, cone->to_o);
	d = vector_length((t_vector*)&op) / cos(cone->r);
	if (op.y < 0.0)
		d = -d;
	on = vector_from_points(&op, &(t_point){0.0, d, 0.0});
	res = normal_mult_tr_matr(&on, cone->to_o);
	return (res);
}

t_vector		get_object_normal(t_point *p, t_object *object)
{
	if (object->type == 's')
		return (vector_from_points(p, &object->point));
	else if (object->type == 'p')
		return (object->vect);
	else if (object->type == 'c')
		return (get_cylinder_normal(p, object));
	else if (object->type == 'k')
		return (get_cone_normal(p, object));
	else
		return ((t_vector){0.0, 0.0, 0.0});
}
