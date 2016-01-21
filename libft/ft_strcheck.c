/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcheck.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/12 11:23:20 by cwagner           #+#    #+#             */
/*   Updated: 2014/03/13 12:21:13 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

int		ft_strcheck(char *str, int (*f)(int))
{
	int		i;

	if (!str)
		return (FAILURE);
	if (!*str || !f)
		return (FAILURE);
	i = 0;
	while (str[i])
	{
		if (f(str[i]) != FT_TRUE)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}
