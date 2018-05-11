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

int		close_win(void)
{
	exit(0);
}

int		key_hook(int keycode, t_rtv *rtv)
{
	if (keycode == 53)
	{
		exit(0);
	}
	if (keycode == 126)
	{
		rtv->cam_ang[0] -= 0.05;
		rtv->cam_tri[0] = cos(rtv->cam_ang[0]);
		rtv->cam_tri[1] = sin(rtv->cam_ang[0]);
		rtv->cam_pos.y -= 0.2;
		rtv->cam_pos.z += 0.2;

		throw_rays(rtv);
	}
	if (keycode == 125)
	{
		rtv->cam_ang[0] += 0.05;
		rtv->cam_tri[0] = cos(rtv->cam_ang[0]);
		rtv->cam_tri[1] = sin(rtv->cam_ang[0]);
		rtv->cam_pos.y += 0.2;
		rtv->cam_pos.z -= 0.2;

		throw_rays(rtv);
	}
	if (keycode == 123)
	{
		rtv->cam_ang[1] += 0.05;
		rtv->cam_tri[2] = cos(rtv->cam_ang[1]);
		rtv->cam_tri[3] = sin(rtv->cam_ang[1]);
		rtv->cam_pos.x -= 0.3;
		rtv->cam_pos.z += 0.3;

		throw_rays(rtv);
	}
	if (keycode == 124)
	{
		rtv->cam_ang[1] -= 0.05;
		rtv->cam_tri[2] = cos(rtv->cam_ang[1]);
		rtv->cam_tri[3] = sin(rtv->cam_ang[1]);
		rtv->cam_pos.x += 0.3;
		rtv->cam_pos.z -= 0.3;

		throw_rays(rtv);
	}
	return (0);
}
