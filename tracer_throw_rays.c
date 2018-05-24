/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer_throw_rays.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 13:53:31 by vchaus            #+#    #+#             */
/*   Updated: 2018/05/24 13:53:32 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

int			tracer(t_vector *ray_dir, t_rtv *rtv)
{
	double	t_min;
	double	t;
	int		obj;
	int		i;

	t_min = INTERS_DIST_INIT;
	obj = MAX_OBJECTS_NUMBER;
	i = 0;
	while (i < rtv->num_obj)
	{
		if ((t = inters_distance(ray_dir, rtv->objects[i], &rtv->cam_pos)) <
																		t_min)
		{
			t_min = t;
			obj = i;
		}
		i++;
	}
	if (obj != MAX_OBJECTS_NUMBER)
		return (res_color_calc(rtv, t_min, ray_dir, obj));
	else
		return (-1);
}

static void	ray_processing(double x, double y, t_rtv *rtv, char *image)
{
	t_vector	ray_dir;
	int			color;

	ray_dir = (t_vector){x, y, FRAME_DISTANCE};
	ray_dir = rotate_cam_ray(rtv->cam_tri, &ray_dir);
	if ((color = tracer(&ray_dir, rtv)) == -1)
		color = rtv->bg_color;
	ft_memcpy(image, &color, 4);
}

void		*throw_rays(void *arg)
{
	double		y;
	double		x;
	char		*image;
	t_thread	*a;

	a = (t_thread*)arg;
	image = a->image;
	y = a->y_start;
	x = a->rtv->x_start;
	while (y < a->y_end)
	{
		while (x < a->rtv->half_frame_w)
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

static void	throw_rays_threads_join(t_rtv *rtv, pthread_t *thread)
{
	int	i;

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

void		throw_rays_threads(t_rtv *rtv)
{
	t_thread	args[THR_NUM];
	pthread_t	thread[THR_NUM];
	int			i;

	i = 0;
	while (i < THR_NUM)
	{
		args[i].rtv = rtv;
		args[i].y_start = rtv->y_start + ((double)(i * rtv->lines_per_thr) *
																	rtv->step);
		args[i].y_end = rtv->y_start + ((double)((i + 1) * rtv->lines_per_thr) *
																	rtv->step);
		args[i].image = rtv->img + (i * rtv->lines_per_thr * IMG_WIDTH * 4);
		if (pthread_create(&thread[i], NULL, throw_rays, &args[i]))
		{
			error_str_null("pthread_create() error");
			destroy_and_exit(rtv);
		}
		i++;
	}
	throw_rays_threads_join(rtv, thread);
}
