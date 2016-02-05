/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 13:05:14 by cwagner           #+#    #+#             */
/*   Updated: 2016/02/05 13:05:17 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void			add_room_to_path(t_path **path, t_room *neighbor)
{
	t_path			*new;
	t_path			*tmp;

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

static int			already_in_pipes(t_path *p, t_room *room)
{
	while (p)
	{
		if (p->neighbor == room)
			return (SUCCESS);
		p = p->next;
	}
	return (FAILURE);
}

static int			verify_room_exists(t_room **rooms, char **split)
{
	t_room			*both[2];
	t_room			*tmp;

	tmp = *rooms;
	both[0] = NULL;
	both[1] = NULL;
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
	if (already_in_pipes(both[0]->torooms, both[1]) == FAILURE)
	{
		add_room_to_path(&both[0]->torooms, both[1]);
		add_room_to_path(&both[1]->torooms, both[0]);
	}
	return (SUCCESS);
}

int					add_pipe(t_room **rooms, char *str)
{
	char			**split;

	if (count_occurences(str, '-') != 1)
		return (error("There must be only 1 '-'"
		"in the pipes. Otherwise I'm lost :("));
	split = ft_strsplit(str, '-');
	if (verify_room_exists(rooms, split) == FAILURE)
		return (FAILURE);
	ft_freechartab(&split);
	return (PIPE);
}
