/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspl_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 17:27:34 by vchaus            #+#    #+#             */
/*   Updated: 2017/12/10 17:27:35 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_del_list_for_split(t_list **root)
{
	t_list	*next;

	while (*root != NULL)
	{
		next = (*root)->next;
		free((*root)->content);
		(*root)->content = NULL;
		free(*root);
		*root = NULL;
		*root = next;
	}
}

static size_t	ft_count_curr_str_for_split(char *s, char c)
{
	size_t	count2;

	if (!ft_strchr(s, c))
		count2 = ft_strchr(s, '\0') - s;
	else
		count2 = ft_strchr(s, c) - s;
	return (count2);
}

static int		ft_lst_el_for_split(char *s, size_t count, t_list **res, char c)
{
	size_t	count2;
	size_t	i;
	t_list	*preslst;

	i = 0;
	while (i < count)
	{
		while (*s == c)
			s++;
		count2 = ft_count_curr_str_for_split(s, c);
		if (!(preslst = ft_lstnew(s, count2 + 1)))
		{
			ft_del_list_for_split(res);
			return (1);
		}
		*((char*)preslst->content + count2) = '\0';
		if (!(*res))
			*res = preslst;
		else
			ft_lstadd_last(res, preslst);
		s += count2;
		i++;
	}
	return (0);
}

t_list			*ft_strspl_lst(char const *s, char c)
{
	size_t	count;
	char	*siter;
	t_list	*res;
	t_list	*lstend;

	res = NULL;
	if (!s)
		return (NULL);
	count = 0;
	siter = (char*)s;
	while (*siter != '\0')
	{
		if (*siter != c && (*(siter + 1) == c || *(siter + 1) == '\0'))
			count++;
		siter++;
	}
	if (ft_lst_el_for_split((char*)s, count, &res, c) == 1)
		return (NULL);
	if (!(lstend = ft_lstnew(NULL, 0)))
		return (NULL);
	if (!res)
		res = lstend;
	else
		ft_lstadd_last(&res, lstend);
	return (res);
}
