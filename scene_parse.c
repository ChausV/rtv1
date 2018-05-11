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
	while(ft_isspace(str[i]))
		i++;
	while(!ft_isspace(str[i]) && str[i] && j < FIRST_WORD_LENGTH - 1)
	{
		(*word)[j] = str[i];
		i++;
		j++;
	}
	(*word)[j] = '\0';
}

void	scene_elems_count_part(int *count, char *type, char value)
{
	(*count)++;
	(*type) = value;
}

int		scene_elems_count(char *first, t_rtv *rtv, t_strlst *elem)
{
	if (ft_strequ(first, "object:"))
		scene_elems_count_part(&rtv->num_obj, &elem->type, 'o');
	else if (ft_strequ(first, "light:"))
		scene_elems_count_part(&rtv->num_lig, &elem->type, 'l');
	else if (first[0] == '#')
		elem->type = 'k';
	else if (ft_strequ(first, "camera:"))
		scene_elems_count_part(&rtv->num_cam, &elem->type, 'c');
	else if (ft_strequ(first, "glare:"))
		scene_elems_count_part(&rtv->num_gla, &elem->type, 'g');
	else if (ft_strequ(first, "shadow:"))
		scene_elems_count_part(&rtv->num_sha, &elem->type, 's');
	else
		return (error_str_int("scene error: unknown element"));
	return (0);
}

int		after_semicolon_check(char *str)
{
	int		i;

	i = 0;
	str = ft_strchr(str, ';');
	str++;
	while(ft_isspace(str[i]))
		i++;
	if (str[i] != '\0')
		return (error_str_int("scene error: semicolon in element description"));
	else
		return (0);
}

int		scene_symbol_check(char *str)
{
	int		i;

	i = 0;
	while(str[i])
	{
		if (!ft_isascii(str[i]))
			return (error_str_int("scene error: non-ascii symbol found"));
		if (!(ft_isprint(str[i]) || ft_isspace(str[i])))
			return (error_str_int("scene error: unallowed ascii symbol found"));
		i++;
	}
	return (0);
}

int		scene_count_and_validation(t_rtv *rtv)
{
	t_strlst	*iter;
	char		word[FIRST_WORD_LENGTH];
	char		*wrd;

	wrd = word;
	iter = rtv->inplst;
	while(iter)
	{
		if (scene_symbol_check(iter->str) != 0)
			return (-1);
		if (ft_strrchr(iter->str, ';') == NULL)
			return (error_str_int("scene error: semicolon not found"));
		if (after_semicolon_check(iter->str) != 0)
			return (-1);
		get_first_word(iter->str, &wrd);
		if (scene_elems_count(word, rtv, iter) != 0)
			return (-1);
		iter = iter->next;
	}
	return (0);
}

int		scene_num_elems_validation(t_rtv *rtv)
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

int		scene_parse(t_rtv *rtv)
{
	if (scene_count_and_validation(rtv) != 0)
		return (-1);
	if (scene_num_elems_validation(rtv) != 0)
		return (-1);
	if (scene_parse_elems(rtv) != 0)
		return (-1);
	return (0);
}
