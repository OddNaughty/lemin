/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/23 23:28:27 by cwagner           #+#    #+#             */
/*   Updated: 2014/03/23 23:28:31 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "libft.h"

# define SUCCESS	0
# define FAILURE	-1
# define PIPED		-3
# define B_ERROR	-2
# define CMD_START	"##start"
# define CMD_END	"##end"

typedef struct		s_lexer
{
	char			*str;
	int				token;
	struct s_lexer	*next;
}					t_lexer;

typedef struct		s_path
{
	struct s_room	*elem;
	struct s_path	*next;
	struct s_path	*prev;
}					t_path;

typedef struct		s_room
{
	char			*name;
	int				x;
	int				y;
	int				flag;
	int				path;
	int				visited;
	int				ants;
	struct s_path	*torooms;
	struct s_room	*prev;
	struct s_room	*next;
}					t_room;

typedef struct		s_dij
{
	char			*name;
	int				path;
	int				visited;
	char			*prev;
	struct s_dij	*next;
}					t_dij;

enum	e_token
{
	ANTS,
	ROOM,
	PIPE,
	CMD,
	START,
	END,
	COM
};

int			error(char *str);

int			tolex(t_room **room, t_lexer **lexed, char *str);

int			isstart(t_room **room, t_lexer **lexed, char *str, int flag);
int			isend(t_room **room, t_lexer **lexed, char *str, int flag);
int			istoroom(t_room **room, t_lexer **lexed, char *str, int flag);
int			ispipe(t_room **room, t_lexer **lexed, char *str, int flag);
int			iscom(t_room **room, t_lexer **lexed, char *str, int flag);
int			isendandstart(t_lexer **lexed);

t_room		*searchit(t_room **room, int flag);
t_dij		*initdij(t_room **room);
t_room		*dodij(t_room **room);

int			sendants(t_room **end, int ants);

int			addtolex(t_lexer **lexer, char *str, int token);
int			addroomtorooms(t_room **copy, t_room *room);
int			addtorooms(t_room **room, char **split, int token);
int			addtodij(t_dij **tab, t_room *room);

t_room		*copyanddelrooms(t_lexer **lexed, t_path **end);
int			deleterooms(t_room **room, t_room **end);
int			deleteone(t_room **room, char *str);

int			applypipe(t_room **room, char *str);
t_path		*newpath(t_room **add);
int			addpathtorooms(t_path **room, t_room **add);
int			checkroomname(t_room **room, char *str1, char *str2);
int			checkoldroom(t_room **room, t_room *new);
t_room		*newroom(t_room **room, char **split, int i);

void		printpath(t_path **room);
void		printend(t_room **room);
void		printroom(t_room **room, int flag);
void		printdij(t_dij **tab);
void		printmap(int ants, t_lexer **lexed);

#endif
