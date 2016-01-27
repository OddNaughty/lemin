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

	(void) av;
	if (ac != 1)
		return (error("Lemin is reading on standard input"));
	if ((map = get_map()) == NULL)
		return (SUCCESS);
	t_room *r;
	r = map->rooms;
	while (r != NULL)
	{
		printf("Room: %s en x: %d en y: %d et de type: %d et ses voisins sont: ", r->name, r->x, r->y, r->type);
		print_neighbor(r->torooms);
		printf("\n");
		r = r->next;
	}
	return (SUCCESS);
}
