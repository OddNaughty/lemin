/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/13 22:59:10 by cwagner           #+#    #+#             */
/*   Updated: 2015/04/13 22:59:19 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H
# define BUFF_SIZE 4096

typedef struct s_gnl	t_gnl;

struct					s_gnl
{
	int			fd;
	char		*wip;
	t_gnl		*next;
};

int						get_next_line(int const fd, char **line);

#endif
