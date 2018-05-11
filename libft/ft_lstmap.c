/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 15:07:01 by vchaus            #+#    #+#             */
/*   Updated: 2017/12/08 15:07:01 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*root;
	t_list	*pres;
	t_list	*prev;

	root = NULL;
	while (lst != NULL && f != NULL)
	{
		if ((pres = f(lst)) == NULL)
		{
			while (root != NULL)
			{
				free(&root);
				root = root->next;
			}
			return (NULL);
		}
		if (root != NULL)
			prev->next = pres;
		if (root == NULL)
			root = pres;
		prev = pres;
		lst = lst->next;
	}
	return (root);
}
