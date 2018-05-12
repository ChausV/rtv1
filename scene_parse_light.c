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

int		parse_light_ambient(char *str, t_rtv *rtv, int *curr)
{
	int		i;
	double	res;

	res = 0.0;
	i = 0;
	skip_space_symbols(str, &i);
	if (word_equ(&str[i], &i, "intensivity"))
		return (error_str_int("scene error: light parse error"));
	skip_space_symbols(str, &i);
	if (parse_double(str, &i, &res) != 0)
	{
		return (error_str_int("scene error: light intensivity error"));
	}
	if (res < 0.0 || res > 1.0)
	{
		return (error_str_int("scene error: light intensivity error"));
	}
	skip_space_symbols(str, &i);
	if (str[i] != ';')
		return (error_str_int("scene error: light parse error"));
	rtv->lights[*curr]->intens = (float)res;
	(*curr)++;
	return (0);
}

int		parse_light(t_rtv *rtv, char *str, int *curr)
{
	int		i;

	i = 0;
	skip_space_symbols(str, &i);
	skip_nonspace_symbols(str, &i);
	skip_space_symbols(str, &i);
	if (!word_equ(&str[i], &i, "point"))
	{
		// return (parse_light_point(&str[i], rtv, curr) ? -1 : 0);
		ft_putendl(&str[i]);
	}
	else if (!word_equ(&str[i], &i, "ambient"))
	{
		rtv->lights[*curr]->type = 'a';
		return (parse_light_ambient(&str[i], rtv, curr) ? -1 : 0);
	}
	else if (!word_equ(&str[i], &i, "directional"))
	{
		// return (parse_light_directional(&str[i], rtv, curr) ? -1 : 0);
		ft_putendl(&str[i]);
	}
	else
		return (error_str_int("scene error: light parse error"));
	return (0);
}
