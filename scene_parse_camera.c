/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 16:11:14 by vchaus            #+#    #+#             */
/*   Updated: 2018/05/10 16:11:15 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

int		word_equ(char *str, int *i, char *word)
{
	int		j;

	j = 0;
	while (!ft_isspace(str[j]) && str[j] != ';' && str[j] != '{')
	{
		if (str[j] != word[j] || word[j] == '\0')
			return (-1);
		j++;
	}
	if (word[j] != '\0')
		return (-1);
	else
	{
		*i += j;
		return (0);
	}
}

void	set_camera_trigonometry(t_rtv *rtv)
{
	rtv->cam_tri[0] = cos(rtv->cam_ang[0]);
	rtv->cam_tri[1] = sin(rtv->cam_ang[0]);
	rtv->cam_tri[2] = cos(rtv->cam_ang[1]);
	rtv->cam_tri[3] = sin(rtv->cam_ang[1]);
	rtv->cam_tri[4] = cos(rtv->cam_ang[2]);
	rtv->cam_tri[5] = sin(rtv->cam_ang[2]);
}

int		parse_camera(t_rtv *rtv, char *str)
{
	int		i;

	i = 0;
	skip_space_symbols(str, &i);
	skip_nonspace_symbols(str, &i);
	skip_space_symbols(str, &i);
	if (word_equ(&str[i], &i, "position") != 0)
		return (error_str_int("scene error: camera parse error"));
	skip_space_symbols(str, &i);
	if (parse_point(&str[i], &i, &rtv->cam_pos) != 0)
		return (error_str_int("scene error: camera position parse error"));
	skip_space_symbols(str, &i);
	if (word_equ(&str[i], &i, "angles") != 0)
		return (error_str_int("scene error: camera parse error"));
	skip_space_symbols(str, &i);
	if (parse_angles(&str[i], &i, rtv->cam_ang) != 0)
		return (error_str_int("scene error: camera angles parse error"));
	skip_space_symbols(str, &i);
	if (str[i] != ';')
		return (error_str_int("scene error: camera parse error"));
	set_camera_trigonometry(rtv);
	return (0);
}
