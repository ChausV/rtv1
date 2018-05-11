/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_point.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 19:41:43 by vchaus            #+#    #+#             */
/*   Updated: 2018/05/10 19:41:44 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

void	parse_double_parts(char *str, int *i, double depth, double *res)
{
	if (depth == 1)
	{
		while(ft_isdigit(str[*i]))
		{
			*res = *res * depth + (double)(str[*i] - 48);
			(*i)++;
			depth *= 10.0;
		}
	}
	else
	{
		while(ft_isdigit(str[*i]))
		{
			*res = *res + depth * (double)(str[*i] - 48);
			(*i)++;
			depth *= 0.1;
		}
	}
}

int		parse_double(char *str, int *i, double *res)
{
	int		sign;

	sign = 1;
	if (str[*i] == '-')
	{
		sign = -1;
		(*i)++;
	}
	else if (str[*i] == '+')
		(*i)++;
	else if (!ft_isdigit(str[*i]))
		return (-1);
	parse_double_parts(str, i, 1.0, res);
	if (str[*i] != '.')
		return (-1);
	(*i)++;
	if (!ft_isdigit(str[*i]))
		return (-1);
	parse_double_parts(str, i, 0.1, res);
	*res *= sign;
	return (0);
}

int		parse_point(char *str, int *i, t_point *point)
{
	int		j;

	j = 0;
	if (str[j] != '{')
		return (-1);
	j++;
	skip_space_symbols(str, &j);
	parse_double(str, &j, &point->x);
	skip_space_symbols(str, &j);
	if (str[j] != ',')
		return (-1);
	j++;
	skip_space_symbols(str, &j);
	parse_double(str, &j, &point->y);
	skip_space_symbols(str, &j);
	if (str[j] != ',')
		return (-1);
	j++;
	skip_space_symbols(str, &j);
	parse_double(str, &j, &point->z);
	skip_space_symbols(str, &j);
	if (str[j] != '}')
		return (-1);
	*i += ++j;
	return (0);
}

int		parse_angles(char *str, int *i, double *angles)
{
	int		j;

	j = 0;
	if (str[j] != '{')
		return (-1);
	j++;
	skip_space_symbols(str, &j);
	parse_double(str, &j, &angles[0]);
	skip_space_symbols(str, &j);
	if (str[j] != ',')
		return (-1);
	j++;
	skip_space_symbols(str, &j);
	parse_double(str, &j, &angles[1]);
	skip_space_symbols(str, &j);
	if (str[j] != ',')
		return (-1);
	j++;
	skip_space_symbols(str, &j);
	parse_double(str, &j, &angles[2]);
	skip_space_symbols(str, &j);
	if (str[j] != '}')
		return (-1);
	*i += ++j;
	return (0);
}
