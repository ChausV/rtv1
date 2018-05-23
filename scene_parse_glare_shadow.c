/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parse_glare_shadow.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 16:19:11 by vchaus            #+#    #+#             */
/*   Updated: 2018/05/23 16:19:12 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

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
