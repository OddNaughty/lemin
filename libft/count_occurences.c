/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_occurences.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 13:50:48 by cwagner           #+#    #+#             */
/*   Updated: 2016/02/05 13:50:56 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		count_occurences(char *str, char c)
{
	int nb_occ;

	nb_occ = 0;
	while (*str)
	{
		if (*str == c)
			nb_occ++;
		str++;
	}
	return (nb_occ);
}
