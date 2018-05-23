/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 19:37:44 by vchaus            #+#    #+#             */
/*   Updated: 2018/05/08 19:37:45 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

void	get_first_word(char *str, char **word)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (ft_isspace(str[i]))
		i++;
	while (!ft_isspace(str[i]) && str[i] && j < FIRST_WORD_LENGTH - 1)
	{
		(*word)[j] = str[i];
		i++;
		j++;
	}
	(*word)[j] = '\0';
}

static int	scene_num_elems_validation(t_rtv *rtv)
{
	if (rtv->num_obj <= 0)
		return (error_str_int("scene error: no object(s)"));
	if (rtv->num_lig <= 0)
		return (error_str_int("scene error: no light(s)"));
	if (rtv->num_cam != 1)
		return (error_str_int("scene error: must contain one camera element"));
	if (rtv->num_gla != 0 && rtv->num_gla != 1)
		return (error_str_int("scene error: must be only one glare rule"));
	if (rtv->num_sha != 0 && rtv->num_sha != 1)
		return (error_str_int("scene error: must be only one shadow rule"));
	return (0);
}

static void	overall_light_intensivity_verification(t_light **lights, int num)
{
	float	all;

	all = 0.0F;
	while (--num >= 0)
	{
		all += lights[num]->intens;
	}
	if (all > 1.0F)
		error_str_int("scene warning: overall lights intensivity warning");
}

int		scene_parse(t_rtv *rtv)
{
	if (scene_count_and_validation(rtv) != 0)
		return (-1);
	if (scene_num_elems_validation(rtv) != 0)
		return (-1);
	if (scene_memory_alloc(rtv) != 0)
		return (-1);
	if (scene_parse_elems(rtv) != 0)
	{
		scene_memory_free(rtv);
		return (-1);
	}
	overall_light_intensivity_verification(rtv->lights, rtv->num_lig);
	return (0);
}
