/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parse_light.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 18:59:05 by vchaus            #+#    #+#             */
/*   Updated: 2018/05/11 18:59:06 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

static int	parse_light_intens(char *str, int *i, float *intens)
{
	double	res;

	res = 0.0;
	skip_space_symbols(str, i);
	if (word_equ(&str[*i], i, "intensivity"))
		return (error_str_int("scene error: light parse error"));
	skip_space_symbols(str, i);
	if (parse_double(str, i, &res) != 0)
	{
		return (error_str_int("scene error: light intensivity error"));
	}
	if (res < 0.0 || res > 1.0)
	{
		return (error_str_int("scene error: light intensivity error"));
	}
	*intens = (float)res;
	skip_space_symbols(str, i);
	return (0);
}

static int	parse_light_ambient(char *str, t_rtv *rtv, int *curr)
{
	int		i;

	i = 0;
	if (parse_light_intens(str, &i, &rtv->lights[*curr]->intens) != 0)
		return (-1);
	if (str[i] != ';')
		return (error_str_int("scene error: light parse error"));
	(*curr)++;
	return (0);
}

static int	parse_light_point(char *str, t_rtv *rtv, int *curr)
{
	int		i;

	i = 0;
	if (parse_light_intens(str, &i, &rtv->lights[*curr]->intens) != 0)
		return (-1);
	if (word_equ(&str[i], &i, "position"))
		return (error_str_int("scene error: light parse error"));
	skip_space_symbols(str, &i);
	if (parse_point(&str[i], &i, &rtv->lights[*curr]->position) != 0)
		return (error_str_int("scene error: light position error"));
	skip_space_symbols(str, &i);
	if (str[i] != ';')
		return (error_str_int("scene error: light parse error"));
	(*curr)++;
	return (0);
}

static int	parse_light_directional(char *str, t_rtv *rtv, int *curr)
{
	int		i;

	i = 0;
	if (parse_light_intens(str, &i, &rtv->lights[*curr]->intens) != 0)
		return (-1);
	if (word_equ(&str[i], &i, "direction"))
		return (error_str_int("scene error: light parse error"));
	skip_space_symbols(str, &i);
	if (parse_vector(&str[i], &i, &rtv->lights[*curr]->direction) != 0)
		return (error_str_int("scene error: light direction error"));
	skip_space_symbols(str, &i);
	if (str[i] != ';')
		return (error_str_int("scene error: light parse error"));
	(*curr)++;
	return (0);
}

int			parse_light(t_rtv *rtv, char *str, int *curr)
{
	int		i;

	i = 0;
	skip_space_symbols(str, &i);
	skip_nonspace_symbols(str, &i);
	skip_space_symbols(str, &i);
	if (!word_equ(&str[i], &i, "point"))
	{
		rtv->lights[*curr]->type = 'p';
		return (parse_light_point(&str[i], rtv, curr) ? -1 : 0);
	}
	else if (!word_equ(&str[i], &i, "ambient"))
	{
		rtv->lights[*curr]->type = 'a';
		return (parse_light_ambient(&str[i], rtv, curr) ? -1 : 0);
	}
	else if (!word_equ(&str[i], &i, "directional"))
	{
		rtv->lights[*curr]->type = 'd';
		return (parse_light_directional(&str[i], rtv, curr) ? -1 : 0);
	}
	else
		return (error_str_int("scene error: light parse error"));
	return (0);
}
