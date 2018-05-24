/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_hook_rotation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 22:53:16 by vchaus            #+#    #+#             */
/*   Updated: 2018/05/24 22:53:17 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

void	rot_up(t_rtv *rtv)
{
	double beta;
	double g;
	double d;

	d = M_PI / 100;
	rtv->cam_ang[0] -= d;
	rtv->cam_tri[0] = cos(rtv->cam_ang[0]);
	rtv->cam_tri[1] = sin(rtv->cam_ang[0]);
	beta = (M_PI / 2.0) + (d / 2.0) - atan2(rtv->cam_pos.z, rtv->cam_pos.y);
	g = 2.0 * sin(d / 2.0) * sqrt(rtv->cam_pos.z * rtv->cam_pos.z +
										rtv->cam_pos.y * rtv->cam_pos.y);
	rtv->cam_pos.y += g * cos(beta);
	rtv->cam_pos.z -= g * sin(beta);
	throw_rays_threads(rtv);
	mlx_put_image_to_window(rtv->mlx[0], rtv->mlx[1], rtv->mlx[2], CADRE + 1,
																	CADRE + 2);
}

void	rot_down(t_rtv *rtv)
{
	double beta;
	double g;
	double d;

	d = M_PI / 100;
	rtv->cam_ang[0] += d;
	rtv->cam_tri[0] = cos(rtv->cam_ang[0]);
	rtv->cam_tri[1] = sin(rtv->cam_ang[0]);
	beta = (M_PI / 2.0) + (d / 2.0) - atan2(rtv->cam_pos.y, rtv->cam_pos.z);
	g = 2.0 * sin(d / 2.0) * sqrt(rtv->cam_pos.z * rtv->cam_pos.z +
										rtv->cam_pos.y * rtv->cam_pos.y);
	rtv->cam_pos.y -= g * sin(beta);
	rtv->cam_pos.z += g * cos(beta);
	throw_rays_threads(rtv);
	mlx_put_image_to_window(rtv->mlx[0], rtv->mlx[1], rtv->mlx[2], CADRE + 1,
																	CADRE + 2);
}

void	rot_right(t_rtv *rtv)
{
	double beta;
	double g;
	double d;

	d = M_PI / 100;
	rtv->cam_ang[1] -= d;
	rtv->cam_tri[2] = cos(rtv->cam_ang[1]);
	rtv->cam_tri[3] = sin(rtv->cam_ang[1]);
	beta = (M_PI / 2.0) + (d / 2.0) - atan2(rtv->cam_pos.z, rtv->cam_pos.x);
	g = 2.0 * sin(d / 2.0) * sqrt(rtv->cam_pos.z * rtv->cam_pos.z +
										rtv->cam_pos.x * rtv->cam_pos.x);
	rtv->cam_pos.x -= g * cos(beta);
	rtv->cam_pos.z += g * sin(beta);
	throw_rays_threads(rtv);
	mlx_put_image_to_window(rtv->mlx[0], rtv->mlx[1], rtv->mlx[2], CADRE + 1,
																	CADRE + 2);
}

void	rot_left(t_rtv *rtv)
{
	double beta;
	double g;
	double d;

	d = M_PI / 100;
	rtv->cam_ang[1] += d;
	rtv->cam_tri[2] = cos(rtv->cam_ang[1]);
	rtv->cam_tri[3] = sin(rtv->cam_ang[1]);
	beta = (M_PI / 2.0) + (d / 2.0) - atan2(rtv->cam_pos.x, rtv->cam_pos.z);
	g = 2.0 * sin(d / 2.0) * sqrt(rtv->cam_pos.z * rtv->cam_pos.z +
										rtv->cam_pos.x * rtv->cam_pos.x);
	rtv->cam_pos.x += g * sin(beta);
	rtv->cam_pos.z -= g * cos(beta);
	throw_rays_threads(rtv);
	mlx_put_image_to_window(rtv->mlx[0], rtv->mlx[1], rtv->mlx[2], CADRE + 1,
																	CADRE + 2);
}
