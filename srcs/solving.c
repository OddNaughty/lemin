//
// Created by Camille WAGNER on 1/27/16.
//

#include <stdio.h>
#include "lemin.h"

t_d			*new_link(t_room *r, t_d *prev)
{
	t_d		*new;

	new = malloc(sizeof(t_d));
	new->room = r;
	new->prev = prev;
	new->next = NULL;
	return (new);
}

void 		add_to_bfs_list(t_d **list, t_d *new)
{
	t_d		*tmp;

	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int 		in_list(t_d *list, t_room *r)
{
	while (list)
	{
		if (list->room == r)
			return (SUCCESS);
		list = list->next;
	}
	return (FAILURE);
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
			if (neighbors->neighbor->selected != FT_TRUE && in_list(visited, neighbors->neighbor) == FAILURE)
			{
				newlink = new_link(neighbors->neighbor, path);
				add_to_bfs_list(&path, newlink);
				newlink = new_link(neighbors->neighbor, path);
				add_to_bfs_list(&visited, newlink);
				if (neighbors->neighbor == e)
					return (newlink);
			}
			neighbors = neighbors->next;
		}
		path = path->next;
	}
	return (NULL);
}

void 		mark_as_selected(t_d **p)
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

void 		add_to_paths(t_paths **paths, t_d *path)
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

t_paths 	*find_paths(t_map *map)
{
	t_d		*path;
	t_paths	*paths;
	t_room	*goals[2] = {NULL, NULL};
	t_room	*tmp;

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
	path = bfs(goals[0], goals[1]);
	while (path)
	{
		add_to_paths(&paths, path);
		mark_as_selected(&path);
		path = bfs(goals[0], goals[1]);
	}
	return (paths);
}

int 		solve_lemin(t_map *map)
{
	t_room	*goals[2] = {NULL, NULL};
	t_room	*tmp;
	t_paths	*paths;

	tmp = map->rooms;
	while (tmp)
	{
		if (tmp->type == START)
			goals[0] = tmp;
		else if (tmp->type == END)
			goals[1] = tmp;
		tmp = tmp->next;
	}
	if ((paths = find_paths(map)) == NULL)
		return (error("No paths was found, bitch"));
	while (paths)
	{
		printf("From end\n");
		t_d *current = paths->current;
		while (current)
		{
			printf("From %s", current->room->name);
			current = current->prev;
		}
		paths = paths->next;
	}
//	path = bfs(goals[0], goals[1]);
//	if (path == NULL)
//		return (error("No paths was found, bitch"));
//	mark_as_selected(&path);
//	ft_putendl("Un autre passage vers la vie ?\n");
//	path = bfs(goals[0], goals[1]);
//	if (path == NULL)
//		return (error("No paths was found, bitch"));
//	mark_as_selected(&path);
//	while (path)
//	{
//		printf("From %s and visited: %d\n", path->room->name, path->room->selected);
//		path = path->prev;
//	}
	return (SUCCESS);
}
