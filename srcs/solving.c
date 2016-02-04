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
	path = bfs(goals[1], goals[0]);
	while (path)
	{
		path = path->prev;
		add_to_paths(&paths, path);
		mark_as_selected(&path);
		path = bfs(goals[1], goals[0]);
	}
	return (paths);
}

void 		count_paths_length(t_paths **paths)
{
	t_paths	*tmp;
	t_d		*tmp2;
	t_d		*tmp3;
	int 	length;

	tmp = *paths;
	while (tmp)
	{
		tmp2 = tmp->current;
		length = 0;
		tmp2->next = NULL;
		while (tmp2)
		{
			tmp3 = tmp2;
			length++;
			tmp2 = tmp2->prev;
			if (tmp2)
				tmp2->next = tmp3;
		}
		tmp->length = length;
		tmp = tmp->next;
	}
}

int 		send_path(t_d *path)
{
	t_d		*tmp;
	t_d		*tmp2;
	int 	success;

	tmp = path;
	success = SUCCESS;
	while (tmp)
	{
		if (tmp->room->ant_number)
		{
			printf("L%d-%s ", tmp->room->ant_number, tmp->room->name);
			success = FAILURE;
		}
		tmp2 = tmp;
		tmp = tmp->prev;
	}
//	printf("Other way %s?\n", tmp2->room->name);
	while (tmp2)
	{
//		printf("Fourmis dans %s: %d\n", tmp2->room->name, tmp2->room->ant_number);
		if (tmp2->next)
			tmp2->room->ant_number = tmp2->next->room->ant_number;
		else
			tmp2->room->ant_number = 0;
		tmp2 = tmp2->next;
	}
	return (success);
}

int 		send_ants(t_paths *paths)
{
	int 	ret;
	int 	ret2;

	ret2 = SUCCESS;
	while (paths)
	{
		ret = send_path(paths->current);
		if (ret == FAILURE)
			ret2 = FAILURE;
		paths = paths->next;
	}
	return (ret2);
}

void 		print_paths(int ants, t_paths *paths)
{
	int sended = 1;

	paths->current->room->ant_number = sended;
	while (send_path(paths->current) != SUCCESS)
	{
		sended++;
		if (sended <= ants)
			paths->current->room->ant_number = sended;
		printf("\n");
	}
}

int 		solve_lemin(t_map *map)
{
	t_paths	*paths;

	if ((paths = find_paths(map)) == NULL)
		return (error("No paths was found, bitch"));
	count_paths_length(&paths);
	print_paths(map->ants, paths);
	return (SUCCESS);
}
