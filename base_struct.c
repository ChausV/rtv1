/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 14:32:23 by vchaus            #+#    #+#             */
/*   Updated: 2018/05/04 14:32:24 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

void	rtv_init(t_rtv *rtv)
{
	rtv->inplst = NULL;
	rtv->num_obj = 0;
	rtv->num_lig = 0;
	rtv->num_cam = 0;
	rtv->num_gla = 0;
	rtv->num_sha = 0;

	// rtv->cam_pos.x = 0.0;
	// rtv->cam_pos.y = 0.0;
	// rtv->cam_pos.z = 0.0;
	// rtv->cam_ang[0] = 0.0;
	// rtv->cam_ang[1] = 0.0;
	// rtv->cam_ang[2] = 0.0;
	// rtv->cam_tri[0] = 0.0;
	// rtv->cam_tri[1] = 0.0;
	// rtv->cam_tri[2] = 0.0;
	// rtv->cam_tri[3] = 0.0;
	// rtv->cam_tri[4] = 0.0;
	// rtv->cam_tri[5] = 0.0;

	rtv->shadow = 0;
	rtv->glare = 0;

	rtv->objects = NULL;
	rtv->lights = NULL;
	// rtv->mlx = NULL;

	rtv->frame_h = ((double)IMG_HEIGHT / (double)IMG_WIDTH) * FRAME_WIDTH;
	rtv->half_frame_w = FRAME_WIDTH / 2.0;
	rtv->half_frame_h = rtv->frame_h / 2.0;
	rtv->step = FRAME_WIDTH / (double)IMG_WIDTH;

	rtv->bg_color = rgb((t_color){100, 100, 100});
	// printf("__%f__\n", rtv->frame_h);
	// printf("step__%f__\n", rtv->step);
}
