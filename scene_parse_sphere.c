/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parse_sphere.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 12:23:16 by vchaus            #+#    #+#             */
/*   Updated: 2018/05/14 12:23:17 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

int		parse_specularity(char *str, int *i, int *specul)
{
	skip_space_symbols(str, i);
	if (word_equ(&str[*i], i, "specularity"))
		return (-1);
	skip_space_symbols(str, i);
	if (parse_integer(str, i, specul) != 0 || *specul < -1)
		return (-1);
	skip_space_symbols(str, i);
	return (0);
}

int		parse_sphere_radius(char *str, int *i, double *radius)
{
	skip_space_symbols(str, i);
	if (word_equ(&str[*i], i, "radius"))
		return (error_str_int("scene error: sphere parse error"));
	skip_space_symbols(str, i);
	if (parse_double(str, i, radius) != 0 || *radius < 0.0)
		return (error_str_int("scene error: sphere radius error"));
	skip_space_symbols(str, i);
	return (0);
}

int		parse_obj_sphere(char *str, t_rtv *rtv, int *curr)
{
	int		i;

	i = 0;
	rtv->objects[*curr]->type = 's';
	skip_space_symbols(str, &i);
	if (word_equ(&str[i], &i, "center"))
		return (error_str_int("scene error: sphere parse error"));
	skip_space_symbols(str, &i);
	if (parse_point(&str[i], &i, &rtv->objects[*curr]->point) != 0)
		return (error_str_int("scene error: sphere center error"));
	if (parse_sphere_radius(str, &i, &rtv->objects[*curr]->r) != 0)
		return (-1);
	if (parse_color(str, &i, &rtv->objects[*curr]->color) != 0)
		return (error_str_int("scene error: sphere color error"));
	if (parse_specularity(str, &i, &rtv->objects[*curr]->specular) != 0)
		return (error_str_int("scene error: sphere specularity error"));
	if (str[i] != ';')
		return (error_str_int("scene error: sphere parse error"));
	(*curr)++;
	return (0);
}
