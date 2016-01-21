//
// Created by Camille WAGNER on 1/21/16.
//

#include "libft.h"
#include "lemin.h"

int 	main(int ac, char **av)
{
	t_map	*map;

	(void) av;
	if (ac != 1)
		return (error("Lemin is reading on standard input"));
	if ((map = get_map()) == NULL)
		return (SUCCESS);
	return (SUCCESS);
}
