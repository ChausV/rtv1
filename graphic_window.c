/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 18:33:05 by vchaus            #+#    #+#             */
/*   Updated: 2018/04/23 18:33:06 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

int		rgb(t_color color)
{
	return (color.r << 16 | color.g << 8 | color.b);
}

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

	a = ray->x * ray->x + ray->z * ray->z;
	b = 2 * (pos->x * ray->x + pos->z * ray->z);
	c = pos->x * pos->x + pos->z * pos->z - cylinder->r * cylinder->r;
	discr = b * b - (4 * a * c);
	if (discr <= 0)
		return (10000000.0);
	t = (-b - sqrt(discr)) / (2 * a);
	if (t > 0)
		return (t);
	else
		return (10000000.0);
}

double	inters_distance(t_vector *ray, t_object *object, t_point *pos)
{
	if (object->type == 's')
		return (interSpher(ray, object, pos));
	else if (object->type == 'p')
		return (interPlane(ray, object, pos));
	else if (object->type == 'c')
		return (interCylinder(ray, object, pos));
	else
		return (10000000.0);
}

t_vector	get_object_normal(t_point *p, t_object *object)
{
	if (object->type == 's')
		return (vector_from_points(p, &object->point));
	else if (object->type == 'p')
		return (object->vect);
	else if (object->type == 'c')
		return (vector_from_points(p, &(t_point){0.0, p->y, 0.0}));
	else
		return ((t_vector){0.0, 0.0, 0.0});
}

int		get_res_color(t_color color, float intense)
{
	int	res_color;

	res_color = rgb((t_color){(int)color.r * intense,
								(int)color.g * intense,
								(int)color.b * intense});
	return (res_color);
}

int		intersect_shadow(t_point *p, t_vector *l, double min, double max, t_rtv *rtv)
{
	int i = 0;
	double	inter;

	while (i < rtv->num_obj)
	{
		inter = inters_distance(l, rtv->objects[i], p);
		if (inter != 10000000.0 && inter <= max && inter >= min)
			return (1);
		i++;
	}
	return (0);
}

float	reflection(t_point *p, t_vector *n, t_vector v, int obj, t_rtv *rtv)
{
	float intens = 0.0F;
	int i;
	double n_dot_l;
	double r_dot_v;
	t_vector l;
	t_vector r;

	i = 0;
	while(i < rtv->num_lig)
	{
		if (rtv->lights[i]->type == 'a')
		{
			intens += rtv->lights[i]->intens;
		}
		else
		{
			if (rtv->lights[i]->type == 'd')
			{
				l = vector_mult_scalar(&rtv->lights[i]->direction, -1);  ///----inverse (look at this later)
				// l = rtv->lights[i]->direction;
				if (rtv->shadow)
				{
					if (intersect_shadow(p, &l, 0.0000001, 10000000.0, rtv) == 1)
					{
						i++;
						continue;
					}
				}
			}
			else if (rtv->lights[i]->type == 'p')
			{
				l = vector_from_points(&rtv->lights[i]->position, p);
				if (rtv->shadow)
				{
					if (intersect_shadow(p, &l, 0.0000001, 1.0, rtv) == 1)
					{
						i++;
						continue;
					}
				}
			}


			n_dot_l = vector_dot_prod(n, &l);
			if (rtv->objects[obj]->type == 'p' && n_dot_l < 0)
				n_dot_l = -n_dot_l;
			if (n_dot_l > 0 )
			{
				intens += rtv->lights[i]->intens * (float)(n_dot_l / (vector_length(n) *
															vector_length(&l)));
			}



			if (rtv->objects[obj]->specular != -1 && rtv->glare)		// check again
			{
				r = vector_mult_scalar(n, 2 * vector_dot_prod(n, &l));
				r = vector_sum(&r, &l, '-');
				r_dot_v = vector_dot_prod(&r, &v);
				if (r_dot_v > 0)
				{
					intens += rtv->lights[i]->intens * (float)pow(r_dot_v / (vector_length(&r) *
												vector_length(&v)), rtv->objects[obj]->specular);
				}
			}


		}
		i++;
	}
	if (intens > 1)
	{
		// printf("___%f___", intens);
		intens = 1;
	}
	return (intens);
}

void	ray_processing(double x, double y, t_rtv *rtv, char *image)
{
	t_vector	ray_dir;
	int			color;

	ray_dir = (t_vector){x, y, FRAME_DISTANCE};
	ray_dir = rotate_cam_ray(rtv->cam_tri, &ray_dir);

	if ((color = tracer(&ray_dir, rtv)) == -1)
		color = rtv->bg_color;
	ft_memcpy(image, &color, 4);
}

void	*throw_rays(void *arg)
{
	double y;
	double x;
	char *image;
	t_thread	*a;

	a = (t_thread*)arg;
	image = a->image;
	y = a->y_start;
	x = a->rtv->x_start;
	while(y < a->y_end)
	{
		while(x < a->rtv->half_frame_w)
		{
			ray_processing(x, y, a->rtv, image);
			x += a->rtv->step;
			image += 4;
		}
		x = a->rtv->x_start;
		y += a->rtv->step;
	}
	return (NULL);
}

void	throw_rays_threads(t_rtv *rtv)
{
	t_thread	args[THR_NUM];
	pthread_t	thread[THR_NUM];
	int			i;

	i = 0;
	while (i < THR_NUM)
	{
		args[i].rtv = rtv;
		args[i].y_start = rtv->y_start + ((double)(i * rtv->lines_per_thr) * rtv->step);
		args[i].y_end = rtv->y_start + ((double)((i + 1) * rtv->lines_per_thr) * rtv->step);
		args[i].image = rtv->img + (i * rtv->lines_per_thr * IMG_WIDTH * 4);
		if (pthread_create(&thread[i], NULL, throw_rays, &args[i]))
		{
			error_str_null("pthread_create() error");
			destroy_and_exit(rtv);
		}
		i++;
	}
	i = 0;
	while (i < THR_NUM)
	{
		if (pthread_join(thread[i], NULL))
		{
			error_str_null("pthread_join() error");
			destroy_and_exit(rtv);
		}
		i++;
	}
}

void	destroy_and_exit(t_rtv *rtv)
{
	mlx_destroy_image(rtv->mlx[0], rtv->mlx[2]);
	mlx_destroy_window(rtv->mlx[0], rtv->mlx[1]);
	scene_memory_free(rtv);
	del_str_lst(&rtv->inplst);
		// system("leaks RTv1");		//=============================
	exit(0);
}

int		mlx_start(t_rtv *rtv)
{
	int		bits_per_pixel;
	int		size_line;
	int		endian;

	bits_per_pixel = 4;							//	WTF ???
	size_line = IMG_WIDTH * bits_per_pixel;		//	WTF ???
	endian = 1;									//	WTF ???
	if (!(rtv->mlx[0] = mlx_init()))
	{
		return (-1);
	}
	if (!(rtv->mlx[1] =
					mlx_new_window(rtv->mlx[0], WIN_WIDTH, WIN_HEIGHT, "RTv1")))
	{
		return (-1);
	}
	if (!(rtv->mlx[2] = mlx_new_image(rtv->mlx[0], IMG_WIDTH, IMG_HEIGHT)))
	{
		mlx_destroy_window(rtv->mlx[0], rtv->mlx[1]);
		return (-1);
	}
	rtv->img =
		mlx_get_data_addr(rtv->mlx[2], &bits_per_pixel, &size_line, &endian);
	return (0);
}

int		graphic_window(t_rtv *rtv)
{
	if (mlx_start(rtv) != 0)
		return (-1);

	throw_rays_threads(rtv);
	mlx_put_image_to_window(rtv->mlx[0], rtv->mlx[1], rtv->mlx[2], 20, 20);


	mlx_hook(rtv->mlx[1], 2, 5, key_hook, rtv);
	mlx_hook(rtv->mlx[1], 17, 1L << 17, close_win, rtv);
	mlx_loop(rtv->mlx[0]);
	return (0);
}
