/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 16:28:52 by vchaus            #+#    #+#             */
/*   Updated: 2018/05/04 16:28:52 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

int				rgb(t_color color)
{
	return (color.r << 16 | color.g << 8 | color.b);
}

static int		get_res_color(t_color color, float intense)
{
	int	res_color;

	res_color = rgb((t_color){(int)color.r * intense,
								(int)color.g * intense,
								(int)color.b * intense});
	return (res_color);
}

static t_point	inters_point(t_point *orig, double t, t_vector *vect)
{
	t_point	res;

	res.x = orig->x + t * vect->x;
	res.y = orig->y + t * vect->y;
	res.z = orig->z + t * vect->z;
	return (res);
}

int				res_color_calc(t_rtv *rtv, double t_min, t_vector *ray_dir,
																		int obj)
{
	t_point		p;
	t_vector	n;
	t_intens	params;
	float		res_intens;
	int			res_color;

	p = inters_point(&rtv->cam_pos, t_min, ray_dir);
	n = get_object_normal(&p, rtv->objects[obj]);
	vector_normalize(&n, &n);
	params.p = &p;
	params.obj = rtv->objects[obj];
	params.n = &n;
	params.rtv = rtv;
	params.ray = vector_mult_scalar(ray_dir, -1);
	params.intens = 0.0F;
	params.i = 0;
	res_intens = res_intensity(&params);
	res_color = get_res_color(rtv->objects[obj]->color, res_intens);
	return (res_color);
}
