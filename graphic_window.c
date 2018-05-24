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

t_vector	rotate_cam_ray(double *trigon, t_vector *vect)
{
	t_vector	res;
	double		tmp_x;
	double		tmp_y;
	double		tmp_z;

	tmp_y = trigon[0] * vect->y - trigon[1] * vect->z;
	tmp_z = trigon[1] * vect->y + trigon[0] * vect->z;
	tmp_x = trigon[2] * vect->x + trigon[3] * tmp_z;
	res.z = -trigon[3] * vect->x + trigon[2] * tmp_z;
	res.x = trigon[4] * tmp_x - trigon[5] * tmp_y;
	res.y = trigon[5] * tmp_x + trigon[4] * tmp_y;
	return (res);
}

void		destroy_and_exit(t_rtv *rtv)
{
	mlx_destroy_image(rtv->mlx[0], rtv->mlx[2]);
	mlx_destroy_window(rtv->mlx[0], rtv->mlx[1]);
	scene_memory_free(rtv);
	del_str_lst(&rtv->inplst);
	exit(0);
}

int			mlx_start(t_rtv *rtv)
{
	int		bits_per_pixel;
	int		size_line;
	int		endian;

	bits_per_pixel = 4;
	size_line = IMG_WIDTH * bits_per_pixel;
	endian = 1;
	if (!(rtv->mlx[0] = mlx_init()))
	{
		return (-1);
	}
	if (!(rtv->mlx[1] = mlx_new_window(rtv->mlx[0], IMG_WIDTH + 2 * CADRE + 3,
										IMG_HEIGHT + 2 * CADRE + 3, "RTv1")))
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

int			graphic_window(t_rtv *rtv)
{
	if (mlx_start(rtv) != 0)
	{
		return (-1);
	}
	draw_frame(rtv->mlx, 0xfffafa);
	throw_rays_threads(rtv);
	mlx_put_image_to_window(rtv->mlx[0], rtv->mlx[1], rtv->mlx[2], CADRE + 1,
																	CADRE + 2);
	mlx_hook(rtv->mlx[1], 2, 5, key_hook, rtv);
	mlx_hook(rtv->mlx[1], 17, 1L << 17, close_win, rtv);
	mlx_loop(rtv->mlx[0]);
	return (0);
}
