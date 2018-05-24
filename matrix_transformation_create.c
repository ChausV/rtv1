/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transformation_create.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 11:11:57 by vchaus            #+#    #+#             */
/*   Updated: 2018/05/21 11:11:58 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

double		matr_determinant(double m[4][4])
{
	double	det;

	if (m[0][3] != 0.0 || m[1][3] != 0.0 ||
		m[2][3] != 0.0 || m[3][3] != 1.0)
		ft_putendl("Warning: you need other determinant function!");
	det = m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) -
			m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) +
			m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
	return (det);
}

void		matr_copy(double dest[4][4], double src[4][4])
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 4)
	{
		while (j < 4)
		{
			dest[i][j] = src[i][j];
			j++;
		}
		j = 0;
		i++;
	}
}

static void	matr_ident_init(double m[4][4])
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 4)
	{
		while (j < 4)
		{
			m[i][j] = 0.0;
			j++;
		}
		j = 0;
		i++;
	}
	j = 0;
	while (j < 4)
	{
		m[j][j] = 1.0;
		j++;
	}
}

static void	create_to_world(t_vector *v, t_object *obj)
{
	t_vector	tmp;
	t_vector	right;
	t_vector	up;

	tmp = (t_vector){0.0, 1.0, 0.0};
	if (fabs(vector_dot_prod(v, &tmp)) > 0.95)
		tmp = (t_vector){1.0, 0.0, 0.0};
	vector_cross_prod(&tmp, v, &right);
	vector_normalize(&right, &right);
	vector_cross_prod(v, &right, &up);
	vector_normalize(&up, &up);
	obj->to_w[0][0] = right.x;
	obj->to_w[0][1] = right.y;
	obj->to_w[0][2] = right.z;
	obj->to_w[0][3] = 0.0;
	obj->to_w[2][0] = up.x;
	obj->to_w[2][1] = up.y;
	obj->to_w[2][2] = up.z;
	obj->to_w[2][3] = 0.0;
}

int			matrix_create(t_vector *v, t_point *p, t_object *obj)
{
	vector_normalize(v, v);
	create_to_world(v, obj);
	obj->to_w[1][0] = v->x;
	obj->to_w[1][1] = v->y;
	obj->to_w[1][2] = v->z;
	obj->to_w[1][3] = 0.0;
	obj->to_w[3][0] = p->x;
	obj->to_w[3][1] = p->y;
	obj->to_w[3][2] = p->z;
	obj->to_w[3][3] = 1.0;
	matr_ident_init(obj->to_o);
	if (matrix_inverse(obj->to_o, obj->to_w) != 0)
		return (-1);
	return (0);
}
