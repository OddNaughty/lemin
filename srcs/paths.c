/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 13:32:32 by cwagner           #+#    #+#             */
/*   Updated: 2016/02/05 13:34:45 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "lemin.h"

static void	mark_as_selected(t_d **p)
{
	t_d		*tmp;

	tmp = *p;
	while (tmp)
	{
		if (tmp->room->type != END && tmp->room->type != START)
			tmp->room->selected = FT_TRUE;
		tmp = tmp->prev;
	}
}

static void	add_to_paths(t_paths **paths, t_d *path)
{
	t_paths	*new;
	t_paths	*tmp;

	new = malloc(sizeof(t_paths));
	new->current = path;
	new->next = NULL;
	if (*paths == NULL)
		*paths = new;
	else
	{
		tmp = *paths;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

static int	count_path_length_and_chaining(t_d **path)
{
	t_d		*tmp;
	t_d		*tmp2;
	int		length;

	length = 0;
	tmp2 = *path;
	tmp2->next = NULL;
	while (tmp2)
	{
		tmp = tmp2;
		length++;
		tmp2 = tmp2->prev;
		if (tmp2)
			tmp2->next = tmp;
	}
	return (length);
}

t_paths		*find_paths(t_map *map)
{
	t_d		*path;
	t_paths	*paths;
	t_room	*goals[2];
	t_room	*tmp;

	goals[0] = NULL;
	goals[1] = NULL;
	tmp = map->rooms;
	while (tmp)
	{
		if (tmp->type == START)
			goals[0] = tmp;
		else if (tmp->type == END)
			goals[1] = tmp;
		tmp = tmp->next;
	}
	paths = NULL;
	path = bfs(goals[1], goals[0]);
	while (path)
	{
		add_to_paths(&paths, path);
		mark_as_selected(&path);
		path = bfs(goals[1], goals[0]);
	}
	return (paths);
}

void		preparing_paths_for_sending(t_paths **paths)
{
	t_paths	*tmp;
	int		min;

	tmp = *paths;
	min = INT_MAX;
	while (tmp)
	{
		if ((tmp->length = count_path_length_and_chaining(&(tmp->current)))
			< min)
			min = tmp->length;
		tmp = tmp->next;
	}
	tmp = *paths;
	while (tmp)
	{
		tmp->length -= min;
		tmp = tmp->next;
	}
}
