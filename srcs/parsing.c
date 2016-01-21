//
// Created by Camille WAGNER on 1/21/16.
//

#include "lemin.h"

int			add_pipe(t_room **rooms, char *str)
{
	return (SUCCESS);
}

int			check_room_validity(char *str)
{
	char	**split;

	split = ft_strsplitwhite(str);
	if (ft_chartablength(split) != 3)
		return (error("A room is defined by nom coord_x coord_y"));
	if (ft_strcheck(split[1], ft_isdigit) == FAILURE || ft_strcheck(split[2], ft_isdigit) == FAILURE)
		return (error("Coordinates must be integers"));
	ft_freechartab(&split);
}

int 		create_room(t_room **rooms, char *str, int type)
{
	t_room	*new;
	char 	**room;

	if (check_room_validity(str) == FAILURE)
		return (FAILURE);
	room = ft_strsplitwhite(str);
	new = malloc(sizeof(t_room));
	new->name = ft_strdup(room[0]);
	new->x = ft_atoi(room[1]);
	new->y = ft_atoi(room[2]);
	return (SUCCESS);
}
