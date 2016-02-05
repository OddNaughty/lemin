/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 12:48:54 by cwagner           #+#    #+#             */
/*   Updated: 2016/02/05 13:29:14 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		check_room_validity(t_room *rooms, char *str)
{
	char	**split;

	split = ft_strsplitwhite(str);
	if (ft_chartablength(split) != 3)
		return (error("A room is defined by nom coord_x coord_y"));
	if (ft_strcheck(split[1], ft_isdigit) == FAILURE ||
			ft_strcheck(split[2], ft_isdigit) == FAILURE)
		return (error("Coordinates must be integers"));
	while (rooms != NULL)
	{
		if (ft_strcmp(rooms->name, split[0]) == SUCCESS)
			return (error("This room got the same name as an other"));
		else if (rooms->x == ft_atoi(split[1]) ||
				rooms->y == ft_atoi(split[2]))
			return (error("This rooms got the same x"
			"or y coordinate as an other"));
		rooms = rooms->next;
	}
	ft_freechartab(&split);
	return (SUCCESS);
}

static t_room	*create_room(t_room *rooms, char *str, int type)
{
	t_room	*new;
	char	**room;

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
	new->selected = FT_FALSE;
	new->ant_number = 0;
	ft_freechartab(&room);
	return (new);
}

int				check_if_pipable(t_room *rooms)
{
	int		errors[2];

	errors[0] = FAILURE;
	errors[1] = FAILURE;
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

int				create_and_add_room(t_room **rooms, char *str, int type)
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
		{
			if (type != ROOM && tmp->type == type)
				return (error(type == END ?
				"There is 2 ends you stupid hobbit" :
				"There is 2 starts you stupid hobbit"));
				tmp = tmp->next;
		}
		tmp->next = new;
	}
	return (SUCCESS);
}
