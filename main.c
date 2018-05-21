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
			del_str_lst(&rtv.inplst);
			return (-1);
		}
		// if (graphic_window(&rtv) != 0)
		// {
		// 	scene_memory_free(&rtv);
		// 	del_str_lst(&rtv.inplst);
		// 	return (-1);
		// }
		// destroy_and_exit(&rtv);
	}
	else
		usage_error(av[0]);
	return (0);
}
