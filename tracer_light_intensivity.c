/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer_light_intensivity.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 15:13:47 by vchaus            #+#    #+#             */
/*   Updated: 2018/05/24 15:13:48 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

int		intersect_shadow(t_point *p, t_vector *l, char flag, t_rtv *rtv)
{
	int		i;
	double	inter;
	double	max;
	double	min;

	min = 0.000001;
	if (flag == 'p')
		max = 1.0;
	else if (flag == 'd')
		max = 1000000.0;
	else
		ft_putendl_fd("intersect_shadow() warning: bad 'flag' argument", 2);
	i = 0;
	while (i < rtv->num_obj)
	{
		inter = inters_distance(l, rtv->objects[i], p);
		if (inter >= min && inter <= max)
			return (1);
		i++;
	}
	return (0);
}

int		direction_of_light(t_intens *p, t_vector *l_dir, t_light *lig)
{
	int		inters;

	inters = 0;
	if (lig->type == 'd')
	{
		*l_dir = vector_mult_scalar(&lig->direction, -1);
		if (p->rtv->shadow)
			inters = intersect_shadow(p->p, l_dir, 'd', p->rtv);
	}
	else if (lig->type == 'p')
	{
		*l_dir = vector_from_points(&lig->position, p->p);
		if (p->rtv->shadow)
			inters = intersect_shadow(p->p, l_dir, 'p', p->rtv);
	}
	else
		ft_putendl_fd("direction_of_light() warning: bad light type", 2);
	if (inters == 1)
	{
		(p->i)++;
		return (1);
	}
	return (0);
}

void	light_intens(t_intens *p, t_vector *l_dir, float i)
{
	float	n_dot_l;

	n_dot_l = (float)vector_dot_prod(p->n, l_dir);
	if (p->obj->type == 'p' && n_dot_l < 0.0)
		n_dot_l = -n_dot_l;
	if (n_dot_l > 0.0F)
	{
		p->intens += i * (n_dot_l / (float)vector_length(l_dir));
	}
}

void	glare_intens(t_intens *p, t_vector *l_dir, float i)
{
	double		r_dot_v;
	t_vector	r;

	if (p->obj->specular != -1 && p->rtv->glare)
	{
		r = vector_mult_scalar(p->n, 2 * vector_dot_prod(p->n, l_dir));
		r = vector_sum(&r, l_dir, '-');
		r_dot_v = vector_dot_prod(&r, &p->ray);
		if (r_dot_v > 0.0)
		{
			p->intens += i * (float)pow(r_dot_v / (vector_length(&r) *
									vector_length(&p->ray)), p->obj->specular);
		}
	}
}

float	res_intensity(t_intens *p)
{
	t_vector	l_dir;

	while (p->i < p->rtv->num_lig)
	{
		if (p->rtv->lights[p->i]->type == 'a')
		{
			p->intens += p->rtv->lights[p->i]->intens;
		}
		else
		{
			if (direction_of_light(p, &l_dir, p->rtv->lights[p->i]))
				continue;
			light_intens(p, &l_dir, p->rtv->lights[p->i]->intens);
			glare_intens(p, &l_dir, p->rtv->lights[p->i]->intens);
		}
		(p->i)++;
	}
	return (p->intens > 1.0 ? 1.0 : p->intens);
}
