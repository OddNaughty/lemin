/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 17:19:30 by cwagner           #+#    #+#             */
/*   Updated: 2016/02/04 17:27:20 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_d	*new_link(t_room *r, t_d *prev)
{
	t_d		*new;

	new = malloc(sizeof(t_d));
	new->room = r;
	new->prev = prev;
	new->next = NULL;
	return (new);
}

static void	add_to_bfs_list(t_d **list, t_d *new)
{
	t_d		*tmp;

	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

static int	in_list(t_d *list, t_room *r)
{
	while (list)
	{
		if (list->room == r)
			return (SUCCESS);
		list = list->next;
	}
	return (FAILURE);
}

static t_d	*just_norme_things(t_d **path, t_d **visited, t_path *neighbors)
{
	t_d		*newlink;

	newlink = new_link(neighbors->neighbor, *path);
	add_to_bfs_list(path, newlink);
	newlink = new_link(neighbors->neighbor, *path);
	add_to_bfs_list(visited, newlink);
	return (newlink);
}

t_d			*bfs(t_room *s, t_room *e)
{
	t_d		*path;
	t_d		*visited;
	t_d		*newlink;
	t_path	*neighbors;

	path = new_link(s, NULL);
	visited = new_link(s, NULL);
	while (path)
	{
		neighbors = path->room->torooms;
		while (neighbors)
		{
			if (neighbors->neighbor->selected != FT_TRUE &&
				in_list(visited, neighbors->neighbor) == FAILURE)
			{
				newlink = just_norme_things(&path, &visited, neighbors);
				if (neighbors->neighbor == e)
					return (newlink);
			}
			neighbors = neighbors->next;
		}
		path = path->next;
	}
	return (NULL);
}
