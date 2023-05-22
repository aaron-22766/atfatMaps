/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:39:05 by arabenst          #+#    #+#             */
/*   Updated: 2023/05/17 15:27:32 by arabenst         ###   ########.fr       */
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

static void	ft_read_map(t_data *data)
{
	int		fd;
	char	*nl;
	size_t	i;

	fd = open(data->input.file, O_RDONLY);
	if (fd == -1)
		ft_error(ERR_READ_FROM_FILE);
	i = -1;
	while (1)
	{
		data->map.map = ft_realloc_map(data->map.map, ++i + 2);
		if (!data->map.map)
		{
			close(fd);
			ft_ferror(data, ERR_MEM);
		}
		data->map.map[i] = get_next_line(fd);
		if (!data->map.map[i])
			break ;
		nl = ft_strchr(data->map.map[i], '\n');
		if (nl)
			nl[0] = 0;
	}
	close(fd);
}

static void	ft_measure_map(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (map->map[++i])
	{
		j = -1;
		while (map->map[i][++j])
		{
			if (map->map[i][j] == COLLECTIBLE)
				map->collects++;
			else if (map->map[i][j] == ENEMY)
				map->enemies++;
		}
		if (j > map->width)
			map->width = j;
	}
	map->height = i;
}

void	ft_get_map(t_data *data)
{
	ft_read_map(data);
	ft_measure_map(&data->map);
}
