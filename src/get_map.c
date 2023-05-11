/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:39:05 by arabenst          #+#    #+#             */
/*   Updated: 2023/05/10 14:04:29 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atfatMaps.h"

static char	**ft_realloc_map(char **ptr, size_t count)
{
	char	**new;
	size_t	i;

	if (count < 2)
		return (NULL);
	if (!ptr)
		return (ft_calloc(count, sizeof(char *)));
	new = ft_calloc(count, sizeof(char *));
	if (!new)
		return (NULL);
	i = -1;
	while (ptr[++i])
		new[i] = ptr[i];
	free(ptr);
	return (new);
}

char	**ft_get_map(char *path)
{
	int		fd;
	char	**map;
	char	*nl;
	size_t	i;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_error(ERR_READ_FROM_FILE);
	map = 0;
	i = -1;
	while (1)
	{
		map = ft_realloc_map(map, ++i + 2);
		if (!map)
			return (NULL);
		map[i] = get_next_line(fd);
		if (!map[i])
			break ;
		nl = ft_strchr(map[i], '\n');
		if (nl)
			nl[0] = 0;
	}
	close(fd);
	return (map);
}
