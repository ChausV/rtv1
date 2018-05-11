/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 14:16:43 by vchaus            #+#    #+#             */
/*   Updated: 2018/02/02 14:16:44 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

void	*error_perror_null(const char *str)
{
	perror(str);
	return (NULL);
}

int		error_perror_int(const char *str)
{
	perror(str);
	return (-1);
}

void	*error_str_null(const char *str)
{
	ft_putendl_fd(str, 2);
	return (NULL);
}

int		error_str_int(const char *str)
{
	ft_putendl_fd(str, 2);
	return (-1);
}

void	usage_error(const char *name)
{
	ft_putstr_fd("usage: ", 2);
	ft_putstr_fd(name, 2);
	ft_putendl_fd(" scene", 2);
}
