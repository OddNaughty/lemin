//
// Created by Camille WAGNER on 1/21/16.
//

#include <stdio.h>
#include "lemin.h"

int			check_if_pipable(t_room *rooms)
{
	int 	errors[2] = {FAILURE, FAILURE};

	while (rooms)
	{
		if (rooms->type == START)
			errors[0] = SUCCESS;
		else if (rooms->type == END)
			errors[1] = SUCCESS;
		rooms = rooms->next;
	}
	if (errors[0] == FAILURE)
		return (error("No start room, we cannot continue"));
	if (errors[1] == FAILURE)
		return (error("No end room, we cannot continue"));
	return (SUCCESS);
}


int			add_pipe(t_room **rooms, char *str)
{
	t_room 	*both[2]= {NULL, NULL};
	t_room	*tmp;
	char 	**split;

	if (count_occurences(str, '-') != 1)
		return (error("There must be only 1 '-' in the pipes. Otherwise I'm lost :("));
	split = ft_strsplit(str, '-');
	tmp = *rooms;
	while (tmp)
	{
		if (ft_strcmp(split[0], tmp->name) == SUCCESS)
			both[0] = tmp;
		else if (ft_strcmp(split[1], tmp->name) == SUCCESS)
			both[1] = tmp;
		tmp = tmp->next;
	}
	if (both[0] == NULL)
		return (error("The first room of the pipe doesn't exists"));
	if (both[1] == NULL)
		return (error("The second room of the pipe doesn't exists"));
	add_room_to_path(&both[0]->torooms, both[1]);
	add_room_to_path(&both[1]->torooms, both[0]);
	ft_freechartab(&split);
	return (PIPE);
}

int			check_room_validity(t_room *rooms, char *str)
{
	char	**split;

	split = ft_strsplitwhite(str);
	if (ft_chartablength(split) != 3)
		return (error("A room is defined by nom coord_x coord_y"));
	if (ft_strcheck(split[1], ft_isdigit) == FAILURE || ft_strcheck(split[2], ft_isdigit) == FAILURE)
		return (error("Coordinates must be integers"));
	while (rooms != NULL)
	{
		if (ft_strcmp(rooms->name, split[0]) == SUCCESS)
			return (error("This room got the same name as an other"));
		else if (rooms->x == ft_atoi(split[1]) || rooms->y == ft_atoi(split[2]))
			return (error("This rooms got the same x or y coordinate as an other"));
		rooms = rooms->next;
	}
	ft_freechartab(&split);
	return (SUCCESS);
}

t_room		*create_room(t_room *rooms, char *str, int type)
{
	t_room	*new;
	char 	**room;

	if (check_room_validity(rooms, str) == FAILURE)
		return (NULL);
	room = ft_strsplitwhite(str);
	new = malloc(sizeof(t_room));
	new->name = ft_strdup(room[0]);
	new->x = ft_atoi(room[1]);
	new->y = ft_atoi(room[2]);
	new->type = type;
	new->next = NULL;
	new->torooms = NULL;
	ft_freechartab(&room);
	return (new);
}

void 		add_room_to_path(t_path **path, t_room *neighbor)
{
	t_path	*new;
	t_path	*tmp;

	new = malloc(sizeof(t_path));
	new->next = NULL;
	new->neighbor = neighbor;
	if (*path == NULL)
		*path = new;
	else
	{
		tmp = *path;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

int 		create_and_add_room(t_room **rooms, char *str, int type)
{
	t_room	*new;
	t_room	*tmp;

	if ((new = create_room(*rooms, str, type)) == NULL)
		return (FAILURE);
	if (*rooms == NULL)
		*rooms = new;
	else
	{
		tmp = *rooms;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (SUCCESS);
}
