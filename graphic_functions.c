/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 16:02:37 by vchaus            #+#    #+#             */
/*   Updated: 2018/05/04 16:02:38 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

int		close_win(t_rtv *rtv)
{
	destroy_and_exit(rtv);
	return (0);
}

int		key_hook(int keycode, t_rtv *rtv)
{
	double beta;
	double g;
	double d;

	d = M_PI / 100;
	if (keycode == 53)
	{
		destroy_and_exit(rtv);
	}
	if (keycode == 126)
	{
		rtv->cam_ang[0] -= d;
		rtv->cam_tri[0] = cos(rtv->cam_ang[0]);
		rtv->cam_tri[1] = sin(rtv->cam_ang[0]);

		beta = (M_PI / 2.0) + (d / 2.0) - atan2(rtv->cam_pos.z, rtv->cam_pos.y);
		g = 2.0 * sin(d / 2.0) * sqrt(rtv->cam_pos.z * rtv->cam_pos.z + rtv->cam_pos.y * rtv->cam_pos.y);
		rtv->cam_pos.y += g * cos(beta);
		rtv->cam_pos.z -= g * sin(beta);

// printf("__d=%f__\n", d);
// printf("__atan=%f__\n", atan(rtv->cam_pos.z / rtv->cam_pos.y) * 2);
// printf("__atan2=%f__\n", atan2(rtv->cam_pos.z, rtv->cam_pos.y) * 2);
// printf("__beta=%f___g=%f__\n", beta, g);
// printf("__sin=%f___cos=%f__\n", sin(beta), cos(beta));
// printf("__%f__\n\n\n", sqrt(rtv->cam_pos.x * rtv->cam_pos.x +
// 						rtv->cam_pos.y * rtv->cam_pos.y +
// 						rtv->cam_pos.z * rtv->cam_pos.z));
		throw_rays_threads(rtv);
		mlx_put_image_to_window(rtv->mlx[0], rtv->mlx[1], rtv->mlx[2], 20, 20);
	}
	if (keycode == 125)
	{
		rtv->cam_ang[0] += d;
		rtv->cam_tri[0] = cos(rtv->cam_ang[0]);
		rtv->cam_tri[1] = sin(rtv->cam_ang[0]);

		beta = (M_PI / 2.0) + (d / 2.0) - atan2(rtv->cam_pos.y, rtv->cam_pos.z);
		g = 2.0 * sin(d / 2.0) * sqrt(rtv->cam_pos.z * rtv->cam_pos.z + rtv->cam_pos.y * rtv->cam_pos.y);
		rtv->cam_pos.y -= g * sin(beta);
		rtv->cam_pos.z += g * cos(beta);

		throw_rays_threads(rtv);
		mlx_put_image_to_window(rtv->mlx[0], rtv->mlx[1], rtv->mlx[2], 20, 20);
	}
	if (keycode == 124)
	{
		rtv->cam_ang[1] -= d;
		rtv->cam_tri[2] = cos(rtv->cam_ang[1]);
		rtv->cam_tri[3] = sin(rtv->cam_ang[1]);

		beta = (M_PI / 2.0) + (d / 2.0) - atan2(rtv->cam_pos.z, rtv->cam_pos.x);
		g = 2.0 * sin(d / 2.0) * sqrt(rtv->cam_pos.z * rtv->cam_pos.z + rtv->cam_pos.x * rtv->cam_pos.x);
		rtv->cam_pos.x -= g * cos(beta);
		rtv->cam_pos.z += g * sin(beta);

		throw_rays_threads(rtv);
		mlx_put_image_to_window(rtv->mlx[0], rtv->mlx[1], rtv->mlx[2], 20, 20);
	}
	if (keycode == 123)
	{
		rtv->cam_ang[1] += d;
		rtv->cam_tri[2] = cos(rtv->cam_ang[1]);
		rtv->cam_tri[3] = sin(rtv->cam_ang[1]);

		beta = (M_PI / 2.0) + (d / 2.0) - atan2(rtv->cam_pos.x, rtv->cam_pos.z);
		g = 2.0 * sin(d / 2.0) * sqrt(rtv->cam_pos.z * rtv->cam_pos.z + rtv->cam_pos.x * rtv->cam_pos.x);
		
		rtv->cam_pos.x += g * sin(beta);
		rtv->cam_pos.z -= g * cos(beta);

		throw_rays_threads(rtv);
		mlx_put_image_to_window(rtv->mlx[0], rtv->mlx[1], rtv->mlx[2], 20, 20);
	}
	return (0);
}
