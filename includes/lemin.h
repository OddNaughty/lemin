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
	int 			selected;
	int 			ant_number;
	struct s_path	*torooms;
	struct s_room	*next;
}					t_room;

typedef struct		s_path
{
	t_room 			*neighbor;
	struct s_path	*next;
}					t_path;

typedef struct		s_map
{
	int 			ants;
	t_room			*rooms;
}					t_map;

typedef struct		s_paths
{
	int				length;
	struct s_d		*current;
	struct s_paths	*next;
}					t_paths;

typedef struct		s_d
{
	t_room			*room;
	struct s_d		*next;
	struct s_d		*prev;
}					t_d;

int 				add_command(t_room **rooms, char *str);
void 				add_room_to_path(t_path **rooms, t_room *new);
int 				add_to_rooms(t_room **rooms, char *str);
int 				add_pipe(t_room **rooms, char *str);
int					check_if_pipable(t_room *rooms);
int					check_room_validity(t_room *rooms, char *str);
t_room				*create_room(t_room *rooms, char *str, int type);
int 				create_and_add_room(t_room **rooms, char *str, int type);

t_d					*bfs(t_room *s, t_room *e);

void 				preparing_paths_for_sending(t_paths **paths);
t_paths 			*find_paths(t_map *map);


t_map 				*get_map();
t_room				*get_rooms();
int					get_ants();

t_d					*bfs(t_room *start, t_room *end);
int 				solve_lemin(t_map *map);

int					exit_error(char *str);
int					error(char *str);

#endif //LEM_IN_LEMIN_H
