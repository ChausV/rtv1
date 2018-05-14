/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_obj_memory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 12:59:44 by vchaus            #+#    #+#             */
/*   Updated: 2018/05/12 12:59:45 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

void	scene_memory_free(t_rtv *rtv)
{
	int		i;

	if (rtv->objects)
	{
		i = 0;
		while (i < rtv->num_obj)
			ft_memdel((void**)&rtv->objects[i++]);
		ft_memdel((void**)rtv->objects);
	}
	if (rtv->lights)
	{
		i = 0;
		while (i < rtv->num_lig)
			ft_memdel((void**)&rtv->lights[i++]);
		ft_memdel((void**)rtv->lights);
	}
}

int		objects_memory_init(t_rtv *rtv)
{
	int		i;

	i = 0;
	while (i < rtv->num_obj)
	{
		if (!(rtv->objects[i] = (t_object*)ft_memalloc(sizeof(t_object))))
		{
			scene_memory_free(rtv);
			return (error_perror_int("ft_memalloc() error"));
		}
		//	attributes initialiization;
		i++;
	}
	return (0);
}

int		lights_memory_init(t_rtv *rtv)
{
	int		i;

	i = 0;
	while (i < rtv->num_lig)
	{
		if (!(rtv->lights[i] = (t_light*)ft_memalloc(sizeof(t_light))))
		{
			scene_memory_free(rtv);
			return (error_perror_int("ft_memalloc() error"));
		}
		//	attributes initialiization;
		i++;
	}
	return (0);
}

int		scene_memory_alloc(t_rtv *rtv)
{
	int		i;

	if (!(rtv->objects = (t_object**)ft_memalloc(sizeof(t_object*)
															* rtv->num_obj)))
		return (error_perror_int("ft_memalloc() error"));
	if (!(rtv->lights = (t_light**)ft_memalloc(sizeof(t_light*)
															* rtv->num_lig)))
	{
		ft_memdel((void**)rtv->objects);
		return (error_perror_int("ft_memalloc() error"));
	}
	i = 0;
	while (i < rtv->num_obj)
		rtv->objects[i++] = NULL;
	i = 0;
	while (i < rtv->num_lig)
		rtv->lights[i++] = NULL;
	if (objects_memory_init(rtv) != 0)
		return (-1);
	if (lights_memory_init(rtv) != 0)
		return (-1);
	return (0);
}
