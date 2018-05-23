/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parse_color.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 12:33:00 by vchaus            #+#    #+#             */
/*   Updated: 2018/05/14 12:33:01 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

int			parse_integer(char *str, int *i, int *target)
{
	int		sign;
	int		res;

	sign = 1;
	res = 0;
	if (str[*i] == '+')
		(*i)++;
	else if (str[*i] == '-')
	{
		sign = -1;
		(*i)++;
	}
	else if (!ft_isdigit(str[*i]))
		return (-1);
	while (ft_isdigit(str[*i]))
	{
		res = res * 10 + (str[(*i)++] - 48);
	}
	res = (sign == 1) ? res : -res;
	*target = res;
	return (0);
}

static int	parse_color_integer(char *str, int *i, int *target)
{
	skip_space_symbols(str, i);
	if (parse_integer(str, i, target) != 0 || *target < 0 || *target > 255)
		return (-1);
	skip_space_symbols(str, i);
	return (0);
}

int			parse_color(char *str, int *i, t_color *target)
{
	skip_space_symbols(str, i);
	if (word_equ(&str[*i], i, "color"))
		return (-1);
	skip_space_symbols(str, i);
	if (str[(*i)++] != '{')
		return (-1);
	if (parse_color_integer(str, i, &target->r) != 0)
		return (-1);
	if (str[(*i)++] != ',')
		return (-1);
	if (parse_color_integer(str, i, &target->g) != 0)
		return (-1);
	if (str[(*i)++] != ',')
		return (-1);
	if (parse_color_integer(str, i, &target->b) != 0)
		return (-1);
	if (str[(*i)++] != '}')
		return (-1);
	skip_space_symbols(str, i);
	return (0);
}
