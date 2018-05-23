/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_count_and_validation.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 15:54:21 by vchaus            #+#    #+#             */
/*   Updated: 2018/05/23 15:54:23 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

static void	scene_elems_count_part(int *count, char *type, char value)
{
	(*count)++;
	(*type) = value;
}

static int	scene_elems_count(char *first, t_rtv *rtv, t_strlst *elem)
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

static int	after_semicolon_check(char *str)
{
	int		i;

	i = 0;
	str = ft_strchr(str, ';');
	str++;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] != '\0')
		return (error_str_int("scene error: semicolon in element description"));
	else
		return (0);
}

static int	scene_symbol_check(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_isascii(str[i]))
			return (error_str_int("scene error: non-ascii symbol found"));
		if (!(ft_isprint(str[i]) || ft_isspace(str[i])))
			return (error_str_int("scene error: unallowed ascii symbol found"));
		i++;
	}
	return (0);
}

int			scene_count_and_validation(t_rtv *rtv)
{
	t_strlst	*iter;
	char		word[FIRST_WORD_LENGTH];
	char		*wrd;

	wrd = word;
	iter = rtv->inplst;
	while (iter)
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
