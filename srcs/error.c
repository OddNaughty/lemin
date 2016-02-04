/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/13 21:31:55 by cwagner           #+#    #+#             */
/*   Updated: 2016/02/04 17:30:00 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		error(char *str)
{
	ft_putstr("Error: ");
	ft_putendl_fd(str, 2);
	return (FAILURE);
}

int		exit_error(char *str)
{
	ft_putstr("Error: ");
	ft_putendl_fd(str, 2);
	exit(FAILURE);
	return (FAILURE);
}
