/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 14:43:49 by vchaus            #+#    #+#             */
/*   Updated: 2018/02/12 14:43:57 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

/*
**	Bresenham's line algorithm
*/

/*
**	first - is octet 0 <= |y1 - y0| <= (x1 - x0)
*/

void	draw_line_int_first(float *p0, float *p1, int color, void **mlx)
{
	int dx;
	int dy;
	int d;
	int y;
	int x;

	x = (int)p0[0];
	y = (int)p0[1];
	dx = (int)p1[0] - x;
	dy = (int)p1[1] - y;
	if (dy < 0)
		dy *= -1;
	d = (2 * dy) - dx;
	while (x <= (int)p1[0])
	{
		mlx_pixel_put(mlx[0], mlx[1], x, y, color);
		if (d > 0)
		{
			((int)p1[1] - (int)p0[1] < 0) ? y-- : y++;
			d += 2 * (dy - dx);
		}
		else
			d += 2 * dy;
		x++;
	}
}

/*
**	second - is octet 0 <= |x1 - x0| <= (y1 - y0)
*/

void	draw_line_int_second(float *p0, float *p1, int color, void **mlx)
{
	int dx;
	int dy;
	int d;
	int y;
	int x;

	x = (int)p0[0];
	y = (int)p0[1];
	dx = (int)p1[0] - x;
	dy = (int)p1[1] - y;
	if (dx < 0)
		dx *= -1;
	d = (2 * dx) - dy;
	while (y <= (int)p1[1])
	{
		mlx_pixel_put(mlx[0], mlx[1], x, y, color);
		if (d > 0)
		{
			((int)p1[0] - (int)p0[0] < 0) ? x-- : x++;
			d += 2 * (dx - dy);
		}
		else
			d += 2 * dx;
		y++;
	}
}

void	draw_line(float *p0, float *p1, int color, void **mlx)
{
	int absx;
	int absy;

	if ((int)p1[0] - (int)p0[0] >= 0)
		absx = (int)p1[0] - (int)p0[0];
	else
		absx = (int)p0[0] - (int)p1[0];
	if ((int)p1[1] - (int)p0[1] >= 0)
		absy = (int)p1[1] - (int)p0[1];
	else
		absy = (int)p0[1] - (int)p1[1];
	if (absy < absx)
	{
		if ((int)p0[0] > (int)p1[0])
			draw_line_int_first(p1, p0, color, mlx);
		else
			draw_line_int_first(p0, p1, color, mlx);
	}
	else
	{
		if ((int)p0[1] > (int)p1[1])
			draw_line_int_second(p1, p0, color, mlx);
		else
			draw_line_int_second(p0, p1, color, mlx);
	}
}
