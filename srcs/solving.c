//
// Created by Camille WAGNER on 1/27/16.
//

#include "lemin.h"

static void 	display(int ant_number, char *room_name)
{
	ft_putstr("L");
	ft_putnbr(ant_number);
	ft_putstr("-");
	ft_putstr(room_name);
	ft_putstr(" ");
}

static int 		send_path(t_d *path)
{
	t_d		*tmp;
	t_d		*tmp2;
	int 	success;

	tmp = path;
	success = SUCCESS;
	while (tmp)
	{
		if (tmp->prev && tmp->room->ant_number)
		{
			display(tmp->room->ant_number, tmp->prev->room->name);
			success = FAILURE;
		}
		tmp2 = tmp;
		tmp = tmp->prev;
	}
	while (tmp2)
	{
		if (tmp2->next)
			tmp2->room->ant_number = tmp2->next->room->ant_number;
		else
			tmp2->room->ant_number = 0;
		tmp2 = tmp2->next;
	}
	return (success);
}

static void 	print_paths(int ants, t_paths *paths)
{
	int 	sended;
	int		success;
	t_paths	*tmp;

	sended = 1;
	while (1)
	{
		success = SUCCESS;
		tmp = paths;
		while (tmp)
		{
			if (sended <= ants && (ants - sended) > tmp->length - 1)
				tmp->current->room->ant_number = sended;
			if (send_path(tmp->current) == FAILURE)
				success = FAILURE;
			tmp = tmp->next;
			sended++;
		}
		if (success == SUCCESS)
			break ;
		ft_putendl("");
	}
}

int 		solve_lemin(t_map *map)
{
	t_paths	*paths;

	if ((paths = find_paths(map)) == NULL)
		return (error("No paths was found, bitch"));
	preparing_paths_for_sending(&paths);
	print_paths(map->ants, paths);
	return (SUCCESS);
}
