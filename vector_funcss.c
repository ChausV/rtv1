/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_funcss.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 22:29:35 by vchaus            #+#    #+#             */
/*   Updated: 2018/05/24 22:29:36 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

t_vector	vector_from_points(t_point *end, t_point *begin)
{
	t_vector	res;

	res.x = end->x - begin->x;
	res.y = end->y - begin->y;
	res.z = end->z - begin->z;
	return (res);
}

t_vector	vector_sum(t_vector *v_1, t_vector *v_2, char sign)
{
	t_vector	res;

	if (sign == '+')
	{
		res.x = v_1->x + v_2->x;
		res.y = v_1->y + v_2->y;
		res.z = v_1->z + v_2->z;
	}
	else if (sign == '-')
	{
		res.x = v_1->x - v_2->x;
		res.y = v_1->y - v_2->y;
		res.z = v_1->z - v_2->z;
	}
	else
	{
		ft_putendl_fd("vector_sum() warning: bad 'sign' argument", 2);
		res.x = 0;
		res.y = 0;
		res.z = 0;
	}
	return (res);
}

t_vector	vector_sum_point(t_vector *v_1, t_vector *v_2, char sign)
{
	t_vector	res;

	if (sign == '+')
	{
		res.x = v_1->x + v_2->x;
		res.y = v_1->y + v_2->y;
		res.z = v_1->z + v_2->z;
	}
	else if (sign == '-')
	{
		res.x = v_1->x - v_2->x;
		res.y = v_1->y - v_2->y;
		res.z = v_1->z - v_2->z;
	}
	else
	{
		ft_putendl_fd("vector_sum_point() warning: bad 'sign' argument", 2);
		res.x = 0;
		res.y = 0;
		res.z = 0;
	}
	return (res);
}

t_vector	vector_mult_scalar(t_vector *vect, double scalar)
{
	t_vector	res;

	res.x = vect->x * scalar;
	res.y = vect->y * scalar;
	res.z = vect->z * scalar;
	return (res);
}
