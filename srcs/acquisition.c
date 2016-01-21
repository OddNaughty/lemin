//
// Created by Camille WAGNER on 1/21/16.
//

#include "lemin.h"

int 	add_command(t_room **rooms, char *str)
{
	int 	type;

	type = FAILURE;
	if (ft_strcmp(str+2, CMD_START) == SUCCESS)
		type = START;
	else if (ft_strcmp(str+2, CMD_END) == SUCCESS)
		type = END;
	else
		ft_putendl("La prochaine commande sera ignorée");
	if (get_next_line(0, &str) < 0)
		return (exit_error("Error while reading file"));
	if (type != FAILURE)
		return (create_room(rooms, str, type));
	return (SUCCESS);
}

int 	add_to_rooms(t_room **rooms, char *str)
{
	if (*str == 'L')
		return (error("A room cannot start with a L"));
	if (*str == '#')
	{
		if (*(str + 1) == '#')
			return (add_command(rooms, str));
		return (SUCCESS);
	}
	if (ft_strchr(str, '-'))
		return (add_pipe(rooms, str));
	return (create_room(rooms, str, ROOM));
}

t_room	*get_rooms_and_pipes()
{
	t_room	*rooms;
	char 	*str;
	int 	ret;

	rooms = NULL;
	while (get_next_line(0, &str) > 0)
	{
		ret = add_to_rooms(&rooms, str);
		ft_strdel(&str);
		if (ret == FAILURE)
			return (NULL);
		else if (ret == PIPE)
			break ;
	}
	return (rooms);
}

int 	get_ants()
{
	char 	*str;
	int 	ants;

	if (get_next_line(0, &str) < 1)
		return (exit_error("Error while reading file"));
	if (ft_strcheck(str, ft_isdigit) == FAILURE)
		return (exit_error("The first line of the file is the NUMBER of ants you dumbass"));
	ants = ft_atoi(str);
	ft_strdel(&str);
	return (ants);
}

t_map 	*get_map()
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	map->ants = get_ants();
	map->rooms = get_rooms_and_pipes();
	if (map->ants == 0 || map->rooms == NULL)
		return (NULL);
	return (map);
}

