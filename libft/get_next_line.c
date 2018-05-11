/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 15:50:16 by vchaus            #+#    #+#             */
/*   Updated: 2018/01/13 15:50:26 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		nl_char_handle(char **tail, char **line)
{
	int		count;
	char	*temp;

	count = 0;
	if (ft_strchr(*tail, '\n'))
	{
		while ((*tail)[count] != '\n')
			count++;
		if (!(*line = ft_strsub(*tail, 0, count)))
		{
			ft_strdel(tail);
			return (-2);
		}
		if (!(temp = ft_strdup((*tail) + count + 1)))
		{
			ft_strdel(tail);
			ft_strdel(line);
			return (-2);
		}
		ft_strdel(tail);
		*tail = temp;
		return (1);
	}
	else
		return (0);
}

static ssize_t	read_once(const int fd, char **str)
{
	char		buf[BUFF_SIZE + 1];
	ssize_t		rret;
	char		*temp;

	ft_bzero(buf, BUFF_SIZE + 1);
	rret = read(fd, buf, BUFF_SIZE);
	temp = *str;
	if (!(*str = ft_strjoin(*str, buf)))
	{
		ft_strdel(str);
		return (-2);
	}
	ft_strdel(&temp);
	return (rret);
}

static int		gnl_processing(const int fd, char **line, char **tail)
{
	ssize_t		rret;
	int			nlret;

	while ((nlret = nl_char_handle(tail, line)) <= 0)
	{
		if (nlret == -2)
			return (-1);
		rret = read_once(fd, tail);
		if (rret < 0)
			return (-1);
		if (rret == 0 && ft_strcmp(*tail, ""))
		{
			*line = *tail;
			if (!(*tail = ft_strnew(0)))
			{
				ft_strdel(line);
				return (-2);
			}
			return (1);
		}
		if (rret == 0 && !ft_strcmp(*tail, ""))
			return (0);
	}
	return (1);
}

static int		ret_dl(t_list *iter, char **line, t_list **tails, const int fd)
{
	int		gnl_ret;
	t_list	*del;

	if ((gnl_ret = gnl_processing((const int)iter->content_size, line, (char**)
		&(iter->content))) < 1 || !ft_strcmp((char*)(iter->content), ""))
	{
		if ((const int)((*tails)->content_size) == fd)
		{
			del = *tails;
			*tails = (*tails)->next;
		}
		else
		{
			iter = *tails;
			while ((const int)(iter->next->content_size) != fd)
				iter = iter->next;
			del = iter->next;
			iter->next = iter->next->next;
		}
		free(del->content);
		free(del);
	}
	return (gnl_ret);
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*tails = NULL;
	t_list			*iter;
	char			*temp;

	if (fd < 0 || !line || !(temp = ft_strnew(fd)))
		return (-1);
	iter = tails;
	while (iter != NULL && (const int)(iter->content_size) != fd)
		iter = iter->next;
	if (iter == NULL)
	{
		if (!(iter = ft_lstnew(temp, fd)))
		{
			ft_strdel(&temp);
			return (-1);
		}
		if (tails == NULL)
			tails = iter;
		else
			ft_lstadd(&tails, iter);
	}
	ft_strdel(&temp);
	return (ret_dl(iter, line, &tails, fd));
}

/*
**	ABOUT buffer:
**	put
**	char		*buf;
**	buf = ft_strnew(BUFF_SIZE);
**	instead of
**	char		buf[BUFF_SIZE + 1];
**	ft_bzero(buf, BUFF_SIZE + 1);
**	for very big BUFF_SIZE (more than ~ 9 000 000)
*/
