/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 13:38:50 by cwagner           #+#    #+#             */
/*   Updated: 2016/02/05 13:46:22 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_LEMIN_H
# define LEM_IN_LEMIN_H

# include "libft.h"

# define CMD_START "start"
# define CMD_END "end"

typedef struct s_room	t_room;
typedef struct s_path	t_path;
typedef struct s_paths	t_paths;
typedef struct s_map	t_map;
typedef struct s_d		t_d;

enum					e_token
{
	ROOM,
	START,
	END,
	PIPE,
	COMMENT,
	COMMAND
};

struct					s_room
{
	char				*name;
	int					x;
	int					y;
	int					type;
	int					selected;
	int					ant_number;
	struct s_path		*torooms;
	struct s_room		*next;
};

struct					s_path
{
	t_room				*neighbor;
	struct s_path		*next;
};

struct					s_map
{
	int					ants;
	t_room				*rooms;
};

struct					s_paths
{
	int					length;
	struct s_d			*current;
	struct s_paths		*next;
};

struct					s_d
{
	t_room				*room;
	struct s_d			*next;
	struct s_d			*prev;
};

int						add_command(t_room **rooms, char *str);
int						add_to_rooms(t_room **rooms, char *str);
int						add_pipe(t_room **rooms, char *str);
int						check_if_pipable(t_room *rooms);
int						create_and_add_room(t_room **r, char *i, int s);

t_d						*bfs(t_room *s, t_room *e);

void					preparing_paths_for_sending(t_paths **paths);
t_paths					*find_paths(t_map *map);

t_map					*get_map();
t_room					*get_rooms();
int						get_ants();

t_d						*bfs(t_room *start, t_room *end);
int						solve_lemin(t_map *map);

int						exit_error(char *str);
int						error(char *str);

#endif
