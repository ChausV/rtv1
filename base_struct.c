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

	rtv->cam_pos.x = 0.0;
	rtv->cam_pos.y = 0.0;
	rtv->cam_pos.z = 0.0;
	rtv->cam_ang[0] = 0.0;
	rtv->cam_ang[1] = 0.0;
	rtv->cam_ang[2] = 0.0;
	// rtv->cam_tri[0] = 0.0;
	// rtv->cam_tri[1] = 0.0;
	// rtv->cam_tri[2] = 0.0;
	// rtv->cam_tri[3] = 0.0;
	// rtv->cam_tri[4] = 0.0;
	// rtv->cam_tri[5] = 0.0;

	rtv->shadow = 0;
	rtv->glare = 0;

	// rtv->objects = NULL;
	// rtv->lights = NULL;
	// rtv->mlx = NULL;
}
