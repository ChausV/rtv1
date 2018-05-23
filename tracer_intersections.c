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

double	interSpher(t_vector *ray_dir, t_object *sphere, t_point *p)
{
	t_vector	o_minus_c;
	double		k[3];
	double		discrim;
	double		t1;
	double		t2;

	o_minus_c = vector_from_points(p, &sphere->point);
	k[0] = vector_dot_prod(ray_dir, ray_dir);
	k[1] = 2 * vector_dot_prod(&o_minus_c, ray_dir);
	k[2] = vector_dot_prod(&o_minus_c, &o_minus_c) - sphere->r * sphere->r;
	discrim = k[1] * k[1] - 4 * k[0] * k[2];
	if (discrim <= 0)
		return (10000000.0);
	t1 = (-k[1] + sqrt(discrim)) / (2 * k[0]);
	t2 = (-k[1] - sqrt(discrim)) / (2 * k[0]);	// t2 is always < t1
	if (t1 < t2 && t1 > 0)
		return (t1);
	else if (t2 < t1 && t2 > 0)
		return (t2);
	else
		return (10000000.0);
}

double	interPlane(t_vector *ray_dir, t_object *plane, t_point *p)
{
	double		t;
	double		n_dot_r;

	if ((n_dot_r = vector_dot_prod(&plane->vect, ray_dir)) == 0)
		return (10000000.0);
	t = -(vector_dot_point(&plane->vect, p) + plane->r) / n_dot_r;
	if (t > 0)
		return (t);
	else
		return (10000000.0);
}

double	interCylinder(t_vector *ray, t_object *cylinder, t_point *pos)
{
	double a;
	double b;
	double c;
	double discr;
	double t;

	t_point		op;
	t_vector	or;

	op = point_mult_matr(pos, cylinder->to_o);
	or = vect_mult_matr(ray, cylinder->to_o);

	a = or.x * or.x + or.z * or.z;
	b = 2 * (op.x * or.x + op.z * or.z);
	c = op.x * op.x + op.z * op.z - cylinder->r * cylinder->r;
	discr = b * b - (4 * a * c);
	if (discr <= 0)
		return (10000000.0);
	t = (-b - sqrt(discr)) / (2 * a);
	if (t > 0)
		return (t);
	else
		return (10000000.0);
}

double	interCone(t_vector *ray, t_object *cone, t_point *pos)
{
	double sqtg;
	double a;
	double b;
	double c;
	double discr;
	double t;

	t_point		op;
	t_vector	or;

	op = point_mult_matr(pos, cone->to_o);
	or = vect_mult_matr(ray, cone->to_o);

	sqtg = tan(cone->r) * tan(cone->r);
	a = or.x * or.x + or.z * or.z - sqtg * or.y * or.y;
	b = 2 * (op.x * or.x + op.z * or.z - sqtg * op.y * or.y);
	c = op.x * op.x + op.z * op.z - sqtg * op.y * op.y;
	discr = b * b - (4 * a * c);
	if (discr <= 0)
	{
		return (10000000.0);
	}
	t = (-b - sqrt(discr)) / (2 * a);
	if (t > 0)
	{
		return (t);
	}
	else
		return (10000000.0);
}

double	inters_distance(t_vector *ray, t_object *object, t_point *pos)
{
	// printf("___t_cone = \n");
	if (object->type == 's')
		return (interSpher(ray, object, pos));
	else if (object->type == 'p')
		return (interPlane(ray, object, pos));
	else if (object->type == 'c')
		return (interCylinder(ray, object, pos));
	else if (object->type == 'k')
		return (interCone(ray, object, pos));
	else
		return (10000000.0);
}
