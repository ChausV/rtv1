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

void	skip_space_symbols(char *str, int *iter)
{
	while (ft_isspace(str[*iter]))
		(*iter)++;
}

void	skip_nonspace_symbols(char *str, int *iter)
{
	while (!ft_isspace(str[*iter]))
		(*iter)++;
}

int		parse_glare(t_rtv *rtv, char *str)
{
	char	buff[SHORT_WORD_LENGTH];
	int		i;
	int		j;

	i = 0;
	j = 0;
	skip_space_symbols(str, &i);
	skip_nonspace_symbols(str, &i);
	skip_space_symbols(str, &i);
	while (!ft_isspace(str[i]) && str[i] != ';' && j < SHORT_WORD_LENGTH - 1)
		buff[j++] = str[i++];
	buff[j] = '\0';
	// ft_putendl(buff);	//=========================
	skip_space_symbols(str, &i);
	if (str[i] != ';')
		return (error_str_int("scene error: glare parse error"));
	if (ft_strequ(buff, "on"))
		rtv->glare = 1;
	else if (ft_strequ(buff, "off"))
		rtv->glare = 0;
	else
		return (error_str_int("scene error: glare parse error"));
	return (0);
}

int		parse_shadow(t_rtv *rtv, char *str)
{
	char	buff[SHORT_WORD_LENGTH];
	int		i;
	int		j;

	i = 0;
	j = 0;
	skip_space_symbols(str, &i);
	skip_nonspace_symbols(str, &i);
	skip_space_symbols(str, &i);
	while (!ft_isspace(str[i]) && str[i] != ';' && j < SHORT_WORD_LENGTH - 1)
		buff[j++] = str[i++];
	buff[j] = '\0';
	// ft_putendl(buff);	//=========================
	skip_space_symbols(str, &i);
	if (str[i] != ';')
		return (error_str_int("scene error: shadow parse error"));
	if (ft_strequ(buff, "on"))
		rtv->shadow = 1;
	else if (ft_strequ(buff, "off"))
		rtv->shadow = 0;
	else
		return (error_str_int("scene error: shadow parse error"));
	return (0);
}

int		scene_parse_el_diff(t_rtv *rtv, t_strlst *elem, int *l_curr, int *o_curr)
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

int		scene_parse_elems(t_rtv *rtv)
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
