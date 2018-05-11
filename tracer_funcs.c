/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 16:28:52 by vchaus            #+#    #+#             */
/*   Updated: 2018/05/04 16:28:52 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

int		res_color_calc(t_rtv *rtv, double t_min, t_vector *ray_dir, int obj)
{
	t_point		p;
	t_vector	n;
	float		res_intense;
	int			res_color;

	p = inters_point(&rtv->cam_pos, t_min, ray_dir);
	n = get_object_normal(&p, rtv->objects[obj]);
	vector_normalize(&n, &n);

	res_intense = reflection(&p, &n, vector_mult_scalar(ray_dir, -1),
										obj, rtv);

	res_color = get_res_color(rtv->objects[obj]->color, res_intense);
	return (res_color);
}

int		tracer(t_vector *ray_dir, t_rtv *rtv)
{
	double	t_min;
	double	t;
	int		obj;
	int 	i;

	t_min = 1000000.0;
	obj = 1000;
	i = 0;
	while(i < rtv->num_obj)
	{
		if ((t = inters_distance(ray_dir, rtv->objects[i], &rtv->cam_pos)) < t_min)
		{
			t_min = t;
			obj = i;
		}
		i++;
	}
	if (obj != 1000)
	{
		return (res_color_calc(rtv, t_min, ray_dir, obj));
	}
	else
	{
		return (-1);
	}
}

t_point	inters_point(t_point *orig, double t, t_vector *vect)
{
	t_point	res;

	res.x = orig->x + t * vect->x;
	res.y = orig->y + t * vect->y;
	res.z = orig->z + t * vect->z;
	return (res);
}

t_vector rotate_cam_ray(double *trigon, t_vector *vect)
{
	t_vector res;
	double tmp_x;
	double tmp_y;
	double tmp_z;

	tmp_y = trigon[0] * vect->y - trigon[1] * vect->z;
	tmp_z = trigon[1] * vect->y + trigon[0] * vect->z;

	tmp_x = trigon[2] * vect->x + trigon[3] * tmp_z;
	res.z = -trigon[3] * vect->x + trigon[2] * tmp_z;

	res.x = trigon[4] * tmp_x - trigon[5] * tmp_y;
	res.y = trigon[5] * tmp_x + trigon[4] * tmp_y;

	return (res);
}
