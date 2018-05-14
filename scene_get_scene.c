/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 13:35:20 by vchaus            #+#    #+#             */
/*   Updated: 2018/05/07 13:35:21 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

int			join_line_in_lst(char **str, char *line)
{
	char	*tmp;

	tmp = ft_strjoin(*str, line);
	if (tmp == NULL)
	{
		free(line);
		return (error_str_int("ft_strjoin() error"));
	}
	free(*str);
	free(line);
	*str = tmp;
	return (0);
}

int			str_to_input_list(char *line, t_rtv *rtv)
{
	if (rtv->inplst == NULL)
	{
		if (!(rtv->inplst = new_str_lst_node()))
		{
			free(line);
			return (-1);
		}
		rtv->inplst->str = line;
	}
	else if (ft_strrchr(rtv->inplst->str, ';'))
	{
		if (str_lst_append_node(&rtv->inplst) != 0)
		{
			free(line);
			return (-1);
		}
		rtv->inplst->str = line;
	}
	else
	{
		if ((join_line_in_lst(&rtv->inplst->str, line)) != 0)
			return (-1);
	}
	return (0);
}

int			get_scene(char *file, t_rtv *rtv)
{
	int			fd;
	char		*line;
	int			gnl_ret;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (error_perror_int("open() error"));
	while ((gnl_ret = get_next_line(fd, &line)) > 0)
	{
		if (str_to_input_list(line, rtv) != 0)
		{
			del_str_lst(&rtv->inplst);
			return (-1);
		}
	}
	if (gnl_ret == -1)
	{
		del_str_lst(&rtv->inplst);
		return (error_str_int("get_next_line() error"));
	}
	if (close(fd) == -1)
	{
		del_str_lst(&rtv->inplst);
		return (error_perror_int("close() error"));
	}
	return (0);
}
