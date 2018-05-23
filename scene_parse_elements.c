/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parse_parse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 18:10:16 by vchaus            #+#    #+#             */
/*   Updated: 2018/05/09 18:10:17 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

void		skip_space_symbols(char *str, int *iter)
{
	while (ft_isspace(str[*iter]))
		(*iter)++;
}

void		skip_nonspace_symbols(char *str, int *iter)
{
	while (!ft_isspace(str[*iter]))
		(*iter)++;
}

static int	scene_parse_el_diff(t_rtv *rtv, t_strlst *elem, int *l_curr,
																	int *o_curr)
{
	if (elem->type == 'o')
	{
		return (parse_object(rtv, elem->str, o_curr) ? -1 : 0);
	}
	if (elem->type == 'l')
	{
		return (parse_light(rtv, elem->str, l_curr) ? -1 : 0);
	}
	if (elem->type == 'c')
	{
		return (parse_camera(rtv, elem->str) ? -1 : 0);
	}
	if (elem->type == 's')
	{
		return (parse_shadow(rtv, elem->str) ? -1 : 0);
	}
	if (elem->type == 'g')
	{
		return (parse_glare(rtv, elem->str) ? -1 : 0);
	}
	return (0);
}

int			scene_parse_elems(t_rtv *rtv)
{
	t_strlst	*iter;
	int			light_curr;
	int			object_curr;

	light_curr = 0;
	object_curr = 0;
	iter = rtv->inplst;
	while (iter)
	{
		if (scene_parse_el_diff(rtv, iter, &light_curr, &object_curr) != 0)
		{
			return (-1);
		}
		iter = iter->next;
	}
	return (0);
}
