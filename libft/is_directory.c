/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_directory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/30 19:23:35 by cwagner           #+#    #+#             */
/*   Updated: 2015/10/30 19:23:38 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "libft.h"

int				is_directory(char *path)
{
	struct stat	mydir;

	if (stat(path, &mydir))
		return (FAILURE);
	return (S_ISDIR(mydir.st_mode));
}
