/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 17:30:20 by cwagner           #+#    #+#             */
/*   Updated: 2016/02/04 17:30:52 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lemin.h"

static void print_map(t_map *map)
{
	t_room	*tmp;

	ft_putnbr(map->ants);
	ft_putendl("");
	tmp = map->rooms;
	while (tmp)
	{

	}
}

int			main(int ac, char **av)
{
	t_map	*map;

	(void)av;
	if (ac != 1)
		return (error("Lemin is reading on standard input"));
	if ((map = get_map()) == NULL)
		return (SUCCESS);
	print_map(map);
	solve_lemin(map);
	return (SUCCESS);
}
