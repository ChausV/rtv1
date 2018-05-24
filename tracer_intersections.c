/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer_intersections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 18:35:14 by vchaus            #+#    #+#             */
/*   Updated: 2018/05/23 18:35:15 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

static double	inter_spher(t_vector *ray_dir, t_object *sphere, t_point *p)
{
	t_vector	o_minus_c;
	double		a[3];
	double		discrim;
	double		t;

	o_minus_c = vector_from_points(p, &sphere->point);
	a[0] = vector_dot_prod(ray_dir, ray_dir);
	a[1] = 2 * vector_dot_prod(&o_minus_c, ray_dir);
	a[2] = vector_dot_prod(&o_minus_c, &o_minus_c) - sphere->r * sphere->r;
	discrim = a[1] * a[1] - 4 * a[0] * a[2];
	if (discrim <= 0)
		return (NO_INTERSEC_DIST);
	t = (-a[1] - sqrt(discrim)) / (2 * a[0]);
	if (t > 0)
		return (t);
	else
		return (NO_INTERSEC_DIST);
}

static double	inter_plane(t_vector *ray_dir, t_object *plane, t_point *p)
{
	double		t;
	double		n_dot_r;

	if ((n_dot_r = vector_dot_prod(&plane->vect, ray_dir)) == 0)
		return (NO_INTERSEC_DIST);
	t = -(vector_dot_point(&plane->vect, p) + plane->r) / n_dot_r;
	if (t > 0)
		return (t);
	else
		return (NO_INTERSEC_DIST);
}

static double	inter_cylinder(t_vector *ray, t_object *cylinder, t_point *pos)
{
	double		a[3];
	double		discr;
	double		t;
	t_point		op;
	t_vector	or;

	op = point_mult_matr(pos, cylinder->to_o);
	or = vect_mult_matr(ray, cylinder->to_o);
	a[0] = or.x * or.x + or.z * or.z;
	a[1] = 2 * (op.x * or.x + op.z * or.z);
	a[2] = op.x * op.x + op.z * op.z - cylinder->r * cylinder->r;
	discr = a[1] * a[1] - (4 * a[0] * a[2]);
	if (discr <= 0)
		return (NO_INTERSEC_DIST);
	t = (-a[1] - sqrt(discr)) / (2 * a[0]);
	if (t > 0)
		return (t);
	else
		return (NO_INTERSEC_DIST);
}

static double	inter_cone(t_vector *ray, t_object *cone, t_point *pos)
{
	double		sqtg;
	double		a[4];
	double		discr;
	t_point		op;
	t_vector	or;

	op = point_mult_matr(pos, cone->to_o);
	or = vect_mult_matr(ray, cone->to_o);
	sqtg = tan(cone->r) * tan(cone->r);
	a[0] = or.x * or.x + or.z * or.z - sqtg * or.y * or.y;
	a[1] = 2 * (op.x * or.x + op.z * or.z - sqtg * op.y * or.y);
	a[2] = op.x * op.x + op.z * op.z - sqtg * op.y * op.y;
	discr = a[1] * a[1] - (4 * a[0] * a[2]);
	if (discr <= 0)
		return (NO_INTERSEC_DIST);
	a[3] = (-a[1] - sqrt(discr)) / (2 * a[0]);
	if (a[3] > 0)
		return (a[3]);
	else
		return (NO_INTERSEC_DIST);
}

double			inters_distance(t_vector *ray, t_object *object, t_point *pos)
{
	if (object->type == 's')
		return (inter_spher(ray, object, pos));
	else if (object->type == 'p')
		return (inter_plane(ray, object, pos));
	else if (object->type == 'c')
		return (inter_cylinder(ray, object, pos));
	else if (object->type == 'k')
		return (inter_cone(ray, object, pos));
	else
		return (NO_INTERSEC_DIST);
}
