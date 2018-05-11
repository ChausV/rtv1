/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_lst_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 19:20:08 by vchaus            #+#    #+#             */
/*   Updated: 2018/05/08 19:20:08 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

t_strlst	*new_str_lst_node()
{
	t_strlst	*elem;

	elem = (t_strlst*)ft_memalloc(sizeof(t_strlst));
	if (elem == NULL)
		return (error_perror_null("ft_memalloc() error"));
	elem->str = NULL;
	elem->next = NULL;
	return (elem);
}

int			str_lst_append_node(t_strlst **list)
{
	t_strlst	*tmp;

	tmp = new_str_lst_node();
	if (tmp == NULL)
		return (-1);
	tmp->next = *list;
	*list = tmp;
	return (0);
}

void		del_str_lst(t_strlst **root)
{
	t_strlst	*iter;
	t_strlst	*temp;

	iter = *root;
	while(iter)
	{
		temp = iter->next;
		free(iter->str);
		free(iter);
		iter = temp;
	}
	*root = NULL;
}
