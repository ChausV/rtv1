/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parse_cylinder_cone.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 17:01:02 by vchaus            #+#    #+#             */
/*   Updated: 2018/05/23 17:01:04 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

static int	parse_point_axis(char *str, int *i, t_rtv *rtv, int *curr)
{
	skip_space_symbols(str, i);
	if (word_equ(&str[*i], i, "point") != 0)
		return (error_str_int("scene error: cylinder parse error"));
	skip_space_symbols(str, i);
	if (parse_point(&str[*i], i, &rtv->objects[*curr]->point) != 0)
		return (error_str_int("scene error: cylinder point error"));
	skip_space_symbols(str, i);
	if (word_equ(&str[*i], i, "axis") != 0)
		return (error_str_int("scene error: cylinder parse error"));
	skip_space_symbols(str, i);
	if (parse_vector(&str[*i], i, &rtv->objects[*curr]->vect) != 0)
		return (error_str_int("scene error: cylinder axis error"));
	skip_space_symbols(str, i);
	return (0);
}

int			parse_obj_cylinder(char *str, t_rtv *rtv, int *curr)
{
	int		i;

	i = 0;
	rtv->objects[*curr]->type = 'c';
	if (parse_point_axis(str, &i, rtv, curr) != 0)
		return (-1);
	if (word_equ(&str[i], &i, "radius"))
		return (error_str_int("scene error: cylinder parse error"));
	skip_space_symbols(str, &i);
	if (parse_double(str, &i, &rtv->objects[*curr]->r) != 0 ||
												rtv->objects[*curr]->r <= 0.0)
		return (error_str_int("scene error: cylinder radius error"));
	if (parse_color(str, &i, &rtv->objects[*curr]->color) != 0)
		return (error_str_int("scene error: cylinder color error"));
	if (parse_specularity(str, &i, &rtv->objects[*curr]->specular) != 0)
		return (error_str_int("scene error: cylinder specularity error"));
	if (str[i] != ';')
		return (error_str_int("scene error: cylinder parse error"));
	if (matrix_create(&rtv->objects[*curr]->vect, &rtv->objects[*curr]->point,
					rtv->objects[*curr]) != 0)
		return (error_str_int("error: inverse matrix creation failed"));
	(*curr)++;
	return (0);
}

int			parse_obj_cone(char *str, t_rtv *rtv, int *curr)
{
	int		i;

	i = 0;
	rtv->objects[*curr]->type = 'k';
	if (parse_point_axis(str, &i, rtv, curr) != 0)
		return (-1);
	if (word_equ(&str[i], &i, "half_angle") != 0)
		return (error_str_int("scene error: cone parse error"));
	skip_space_symbols(str, &i);
	if (parse_double(str, &i, &rtv->objects[*curr]->r) != 0 ||
		rtv->objects[*curr]->r <= 0.0 || rtv->objects[*curr]->r >= (M_PI / 2.0))
		return (error_str_int("scene error: cone angle error"));
	if (parse_color(str, &i, &rtv->objects[*curr]->color) != 0)
		return (error_str_int("scene error: cone color error"));
	if (parse_specularity(str, &i, &rtv->objects[*curr]->specular) != 0)
		return (error_str_int("scene error: cone specularity error"));
	if (str[i] != ';')
		return (error_str_int("scene error: cone parse error"));
	if (matrix_create(&rtv->objects[*curr]->vect, &rtv->objects[*curr]->point,
					rtv->objects[*curr]) != 0)
		return (error_str_int("error: inverse matrix creation failed"));
	(*curr)++;
	return (0);
}
