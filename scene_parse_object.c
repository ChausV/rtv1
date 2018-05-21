/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parse_object.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 11:40:21 by vchaus            #+#    #+#             */
/*   Updated: 2018/05/14 11:40:22 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

void	plane_norm_and_d(t_object *plane)
{
	vector_normalize(&plane->vect, &plane->vect);
	plane->r = -vector_dot_point(&plane->vect, &plane->point);
}

int		parse_obj_plane(char *str, t_rtv *rtv, int *curr)
{
	int		i;

	i = 0;
	rtv->objects[*curr]->type = 'p';
	skip_space_symbols(str, &i);
	if (word_equ(&str[i], &i, "point") != 0)
		return (error_str_int("scene error: plane parse error"));
	skip_space_symbols(str, &i);
	if (parse_point(&str[i], &i, &rtv->objects[*curr]->point) != 0)
		return (error_str_int("scene error: plane point error"));
	skip_space_symbols(str, &i);
	if (word_equ(&str[i], &i, "normal") != 0)
		return (error_str_int("scene error: plane parse error"));
	skip_space_symbols(str, &i);
	if (parse_vector(&str[i], &i, &rtv->objects[*curr]->vect) != 0)
		return (error_str_int("scene error: plane normal error"));
	if (parse_color(str, &i, &rtv->objects[*curr]->color) != 0)
		return (error_str_int("scene error: plane color error"));
	if (parse_specularity(str, &i, &rtv->objects[*curr]->specular) != 0)
		return (error_str_int("scene error: plane specularity error"));
	if (str[i] != ';')
		return (error_str_int("scene error: plane parse error"));
	plane_norm_and_d(rtv->objects[*curr]);
	(*curr)++;
	return (0);
}

int		parse_obj_cylinder(char *str, t_rtv *rtv, int *curr)
{
	int		i;

	i = 0;
	rtv->objects[*curr]->type = 'c';
	skip_space_symbols(str, &i);
	if (word_equ(&str[i], &i, "point") != 0)
		return (error_str_int("scene error: cylinder parse error"));
	skip_space_symbols(str, &i);
	if (parse_point(&str[i], &i, &rtv->objects[*curr]->point) != 0)
		return (error_str_int("scene error: cylinder point error"));
	skip_space_symbols(str, &i);
	if (word_equ(&str[i], &i, "axis") != 0)
		return (error_str_int("scene error: cylinder parse error"));
	skip_space_symbols(str, &i);
	if (parse_vector(&str[i], &i, &rtv->objects[*curr]->vect) != 0)
		return (error_str_int("scene error: cylinder normal error"));

	skip_space_symbols(str, &i);
	if (word_equ(&str[i], &i, "radius"))
		return (error_str_int("scene error: cylinder parse error"));
	skip_space_symbols(str, &i);
	if (parse_double(str, &i, &rtv->objects[*curr]->r) != 0 || rtv->objects[*curr]->r < 0.0)
		return (error_str_int("scene error: cylinder radius error"));

	if (parse_color(str, &i, &rtv->objects[*curr]->color) != 0)
		return (error_str_int("scene error: cylinder color error"));
	if (parse_specularity(str, &i, &rtv->objects[*curr]->specular) != 0)
		return (error_str_int("scene error: cylinder specularity error"));
	if (str[i] != ';')
		return (error_str_int("scene error: cylinder parse error"));


	matrix_create(&rtv->objects[*curr]->vect, &rtv->objects[*curr]->point,
					rtv->objects[*curr]);


	(*curr)++;
	return (0);
}

int		parse_obj_cone(char *str, t_rtv *rtv, int *curr)
{
	int		i;

	i = 0;
	rtv->objects[*curr]->type = 'k';
	skip_space_symbols(str, &i);
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

	(*curr)++;
	return (0);
}

int		parse_object(t_rtv *rtv, char *str, int *curr)
{
	int		i;

	i = 0;
	skip_space_symbols(str, &i);
	skip_nonspace_symbols(str, &i);
	skip_space_symbols(str, &i);
	if (!word_equ(&str[i], &i, "sphere"))
	{
		return (parse_obj_sphere(&str[i], rtv, curr) ? -1 : 0);
	}
	else if (!word_equ(&str[i], &i, "plane"))
	{
		return (parse_obj_plane(&str[i], rtv, curr) ? -1 : 0);
	}
	else if (!word_equ(&str[i], &i, "cylinder"))
	{
		return (parse_obj_cylinder(&str[i], rtv, curr) ? -1 : 0);
	}
	else if (!word_equ(&str[i], &i, "cone"))
	{
		return (parse_obj_cone(&str[i], rtv, curr) ? -1 : 0);
	}
	else
	{
		return (error_str_int("scene error: objects parse error"));
	}
	return (0);
}
