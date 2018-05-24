/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_hook_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 16:02:37 by vchaus            #+#    #+#             */
/*   Updated: 2018/05/04 16:02:38 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

int		close_win(t_rtv *rtv)
{
	destroy_and_exit(rtv);
	return (0);
}

int		key_hook(int keycode, t_rtv *rtv)
{
	if (keycode == 53)
	{
		destroy_and_exit(rtv);
	}
	if (keycode == 126)
	{
		rot_up(rtv);
	}
	if (keycode == 125)
	{
		rot_down(rtv);
	}
	if (keycode == 124)
	{
		rot_right(rtv);
	}
	if (keycode == 123)
	{
		rot_left(rtv);
	}
	return (0);
}
