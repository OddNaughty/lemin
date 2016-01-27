//
// Created by Camille WAGNER on 1/21/16.
//

#include "libft.h"
#include "lemin.h"
#include <stdio.h>

void 	print_neighbor(t_path *s)
{
	while (s)
	{
		printf("%s ", s->neighbor->name);
		s = s->next;
	}
}

int 	main(int ac, char **av)
{
	t_map	*map;
//	t_room	*tmp;

	(void) av;
	if (ac != 1)
		return (error("Lemin is reading on standard input"));
	if ((map = get_map()) == NULL)
		return (SUCCESS);
//	tmp = map->rooms;
//	while (tmp)
//	{
//		printf("Room %s and it neighbors: ", tmp->name);
//		print_neighbor(tmp->torooms);
//		printf("\n");
//		tmp = tmp->next;
//	}
	solve_lemin(map);
	return (SUCCESS);
}
