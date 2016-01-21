//
// Created by Camille WAGNER on 1/21/16.
//

#ifndef LEM_IN_LEMIN_H
# define LEM_IN_LEMIN_H

#include "libft.h"

#define CMD_START "start"
#define CMD_END "end"

enum	e_token
{
	ROOM,
	START,
	END,
	PIPE
};


typedef struct		s_room
{
	char			*name;
	int				x;
	int				y;
	int				type;
	struct s_path	*torooms;
	struct s_room	*next;
}					t_room;

typedef struct		s_map
{
	int 			ants;
	t_room			*rooms;
}					t_map;

int 				add_command(t_room **rooms, char *str);
int 				add_to_rooms(t_room **rooms, char *str);
int 				add_pipe(t_room **rooms, char *str);
int 				create_room(t_room **rooms, char *str, int type);

t_map 				*get_map();
t_room				*get_rooms();
int					get_ants();

int					exit_error(char *str);
int					error(char *str);

#endif //LEM_IN_LEMIN_H