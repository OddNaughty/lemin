/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/13 22:58:05 by cwagner           #+#    #+#             */
/*   Updated: 2015/04/13 22:58:09 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "get_next_line.h"

static int	read_line2(int fd, char **wip)
{
	char	*buf;
	int		rode;

	if ((buf = ft_strnew(BUFF_SIZE + 1)) == NULL)
		return (FAILURE);
	while ((rode = read(fd, buf, BUFF_SIZE)) > 0)
	{
		*wip = ft_strfreejoin(wip, buf);
		if (ft_strchr(buf, '\n') != NULL)
			break ;
		ft_strclr(buf);
	}
	ft_strdel(&buf);
	if (rode == 0 && *wip == NULL)
		return (0);
	return (rode == -1 ? -1 : 1);
}

void		wip_to_line(char **line, char **wip)
{
	char	*n;
	char	*tmp;

	n = ft_strchr(*wip, '\n');
	if (n == NULL)
	{
		*line = ft_strdup(*wip);
		ft_strdel(wip);
		return ;
	}
	*line = ft_strsub(*wip, 0, ft_strlen(*wip) - ft_strlen(n));
	tmp = ft_strsub(*wip, ft_strlen(*line) + 1, ft_strlen(n + 1));
	ft_strdel(wip);
	if (ft_strlen(tmp))
		*wip = tmp;
}

void		free_list(t_gnl **b_list)
{
	t_gnl	*tmp;

	while (*b_list)
	{
		tmp = *b_list;
		ft_strdel(&(tmp->wip));
		*b_list = tmp->next;
		free(tmp);
	}
	*b_list = NULL;
}

t_gnl		*add_to_list(t_gnl **b_list, int fd)
{
	t_gnl	*new_one;
	t_gnl	*tmp;

	new_one = malloc(sizeof(t_gnl));
	new_one->fd = fd;
	new_one->wip = NULL;
	new_one->next = NULL;
	if (*b_list == NULL)
		*b_list = new_one;
	else
	{
		tmp = *b_list;
		while (tmp->next && tmp->fd != fd)
			tmp = tmp->next;
		if (tmp->fd != fd)
			tmp->next = new_one;
		else
			return (free(new_one), tmp);
	}
	return (new_one);
}

int			get_next_line(int const fd, char **line)
{
	static t_gnl	*b_list = NULL;
	t_gnl			*link;
	int				ret;

	if (!line)
		return (FAILURE);
	*line = NULL;
	link = add_to_list(&b_list, fd);
	if (link->wip == NULL || ft_strchr(link->wip, '\n') == NULL)
		if ((ret = read_line2(fd, &(link->wip))) != 1)
			return (free_list(&b_list), ret);
	wip_to_line(line, &(link->wip));
	return (1);
}
