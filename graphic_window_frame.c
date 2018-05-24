/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_window_frame.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 23:45:57 by vchaus            #+#    #+#             */
/*   Updated: 2018/05/24 23:45:58 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

void	draw_frame_two(void **mlx, int color)
{
	float	p1[2];
	float	p2[2];
	float	p3[2];
	float	p4[2];

	p1[0] = 0.0F;
	p1[1] = 0.0F;
	p2[0] = (float)(IMG_WIDTH + 2 * (CADRE + 1));
	p2[1] = 0.0F;
	p3[0] = 0.0F;
	p3[1] = (float)(IMG_HEIGHT + 2 * (CADRE + 1));
	p4[0] = (float)(IMG_WIDTH + 2 * (CADRE + 1));
	p4[1] = (float)(IMG_HEIGHT + 2 * (CADRE + 1));
	draw_line(p1, p2, color, mlx);
	draw_line(p3, p4, color, mlx);
	draw_line(p1, p3, color, mlx);
	draw_line(p2, p4, color, mlx);
}

void	draw_frame(void **mlx, int color)
{
	float	p1[2];
	float	p2[2];
	float	p3[2];
	float	p4[2];

	draw_frame_two(mlx, color);
	p1[0] = (float)(CADRE);
	p1[1] = (float)(CADRE);
	p2[0] = (float)(IMG_WIDTH + CADRE + 2);
	p2[1] = (float)(CADRE);
	p3[0] = (float)(CADRE);
	p3[1] = (float)(IMG_HEIGHT + CADRE + 2);
	p4[0] = (float)(IMG_WIDTH + CADRE + 2);
	p4[1] = (float)(IMG_HEIGHT + CADRE + 2);
	draw_line(p1, p2, color, mlx);
	draw_line(p3, p4, color, mlx);
	draw_line(p1, p3, color, mlx);
	draw_line(p2, p4, color, mlx);
}
