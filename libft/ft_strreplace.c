/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/30 19:23:48 by cwagner           #+#    #+#             */
/*   Updated: 2015/10/30 19:23:54 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strreplace(char *s, char *to_find, char *replace)
{
	char	*translated;
	char	*occurence;
	char	*leak;
	size_t	where;

	if (!to_find || !*to_find || !s)
		return (ft_strdup(s));
	if (!(occurence = ft_strstr(s, to_find)))
		return (ft_strdup(s));
	where = ft_strlen(s) - ft_strlen(occurence) + ft_strlen(to_find);
	translated = ft_strsub(s, 0, where - ft_strlen(to_find));
	translated = ft_strfreejoin(&translated, replace);
	s += where;
	while (*s && (occurence = ft_strstr(s, to_find)))
	{
		where = ft_strlen(s) - ft_strlen(occurence) + ft_strlen(to_find);
		leak = ft_strsub(s, 0, where - ft_strlen(to_find));
		translated = ft_strfreejoin(&translated, leak);
		ft_strdel(&leak);
		translated = ft_strfreejoin(&translated, replace);
		s += where;
	}
	translated = ft_strfreejoin(&translated, s);
	return (translated);
}
