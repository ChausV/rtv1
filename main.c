/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 14:18:07 by vchaus            #+#    #+#             */
/*   Updated: 2018/02/12 14:18:08 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		t_rtv	rtv;

		rtv_init(&rtv);
		if (get_scene(av[1], &rtv) != 0)
		{
			return (-1);
		}
		if (scene_parse(&rtv) != 0)
		{
			//	free strlst
			return (-1);
		}

		// printf("__obj: %d\n", rtv.num_obj);
		// printf("__lig: %d\n", rtv.num_lig);
		// printf("__cam: %d\n", rtv.num_cam);
		// printf("__gla: %d\n", rtv.num_gla);
		// printf("__sha: %d\n", rtv.num_sha);



		t_strlst	*iter;
		iter = rtv.inplst;
		while (iter)
		{
			if (iter->type != 'k')
			{
				ft_putendl(iter->str);
				ft_putchar(iter->type);
				ft_putchar('\n');
			}
			iter = iter->next;
		}

		// rtv.inplst = NULL;
		// del_str_lst(&rtv.inplst);
		// system("leaks RTv1");




		rtv.num_obj = 11;
		rtv.num_lig = 4;
		t_object *objects[rtv.num_obj];
		t_light *light[rtv.num_lig];

		t_object sphere0 = {'s', {2.0, 0.0, 5.0}, {0, 0, 0}, 2.0, {255, 0, 0}, 100};
		t_object sphere1 = {'s', {0.0, 0.0, 5.0}, {0, 0, 0}, 2.0, {0, 255, 0}, 100};
		t_object sphere2 = {'s', {-2.0, 0.0, 5.0}, {0, 0, 0}, 2.0, {0, 0, 255}, 100};
		t_object sphere3 = {'s', {0.0, 1.0, 4.0}, {0, 0, 0}, 0.7, {100, 0, 0}, 100};
		t_object sphere4 = {'s', {0.0, -1.5, 3.5}, {0, 0, 0}, 0.4, {0, 0, 150}, 100};
		t_object sphere5 = {'s', {1.0, 0.0, 4.1}, {0, 0, 0}, 1.0, {255, 255, 255}, 100};
		t_object sphere6 = {'s', {0.0, 0.0, 1.5}, {0, 0, 0}, 0.2, {255, 255, 255}, 100};
		t_object sphere7 = {'s', {0.0, 45.0, 25.0}, {0, 0, 0}, 45.0, {255, 255, 0}, 100};
		t_object sphere8 = {'s', {0.0, 0.0, 2.0}, {0, 0, 0}, 0.05, {150, 150, 150}, 100};
		t_object plane9 = {'p', {0.0, 3.5, 0.0}, {0, -1, 0}, 0.0, {0, 255, 0}, 100};
			vector_normalize(&plane9.vect, &plane9.vect);
			plane9.r = -vector_dot_point(&plane9.vect, &plane9.point);
			// printf("___%f___\n", plane9.r);
		t_object plane10 = {'p', {0.0, 0.0, 10.0}, {0, 0, -1}, 0.0, {200, 200, 200}, 100};
			vector_normalize(&plane10.vect, &plane10.vect);
			plane10.r = -vector_dot_point(&plane10.vect, &plane10.point);
		objects[0] = &sphere0;
		objects[1] = &sphere1;
		objects[2] = &sphere2;
		objects[3] = &sphere3;
		objects[4] = &sphere4;
		objects[5] = &sphere5;
		objects[6] = &sphere6;
		objects[7] = &sphere7;
		objects[8] = &sphere8;
		objects[9] = &plane9;
		objects[10] = &plane10;

		t_light light0 = {'a', 0.2F, {0, 0, 0}, {0, 0, 0}};
		t_light light1 = {'p', 0.6F, {4, -4, -4}, {0, 0, 0}};
		t_light light2 = {'d', 0.2F, {0, 0, 0}, {1, 1, 1}};
		t_light light3 = {'p', 0.0F, {0, 0, 0}, {0, 0, 0}};
		light[0] = &light0;
		light[1] = &light1;
		light[2] = &light2;
		light[3] = &light3;

		rtv.objects = objects;
		rtv.lights = light;



		if (graphic_window(&rtv) != 0)
			return (-1);
		write(1, "-----------------------graphic_window---------------------", 60);
	}
	else
	{
		usage_error(av[0]);
	}
	return (0);
}
