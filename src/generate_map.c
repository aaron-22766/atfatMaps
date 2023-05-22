/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:06:58 by arabenst          #+#    #+#             */
/*   Updated: 2023/05/17 14:59:28 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atfatMaps.h"

static void	ft_set_map(t_data *data)
{
	data->map.width = 5 + rand() % 35;
	if (data->input.map_input.width != -1)
		data->map.width = data->input.map_input.width;
	data->map.height = 5 + rand() % 35;
	if (data->input.map_input.height != -1)
		data->map.height = data->input.map_input.height;
	data->map.collects = 1 + rand()
		% ft_sqrt(data->map.width * data->map.height);
	if (data->input.map_input.collects != -1)
		data->map.collects = data->input.map_input.collects;
	data->map.enemies = rand()
		% (ft_sqrt(data->map.width * data->map.height) - 3);
	if (data->input.map_input.enemies != -1)
		data->map.enemies = data->input.map_input.enemies;
}

static void	ft_make_grid_map(t_data *data)
{
	int	i;
	int	j;

	data->map.map = ft_calloc(data->map.height + 1, sizeof(char *));
	if (!data->map.map)
		ft_ferror(data, ERR_MEM);
	i = -1;
	while (++i < data->map.height)
	{
		data->map.map[i] = ft_calloc(data->map.width + 1, sizeof(char));
		if (!data->map.map[i])
			ft_ferror(data, ERR_MEM);
		if (i % 2 == 0 || i == data->map.height - 1)
			ft_memset(data->map.map[i], WALL, data->map.width);
		else
			ft_memset(data->map.map[i], UNVISITED, data->map.width);
		j = -1;
		while (++j < data->map.width)
			if (j % 2 == 0 || j == data->map.width - 1)
				data->map.map[i][j] = WALL;
	}
}

static void	ft_add_spikes(t_map *map, int x, int y)
{
	int	target;

	if (y == 1)
	{
		while (y < map->width - 1)
		{
			target = y + 1 + 2 * (rand() % 3);
			while (y < target && y < map->width - 1)
				map->map[x][y++] = PATH;
			y += 3;
		}
		return ;
	}
	while (x < map->height - 1)
	{
		target = x + 1 + 2 * (rand() % 3);
		while (x < target && x < map->height - 1)
			map->map[x++][y] = PATH;
		x += 3;
	}
}

static void	ft_spawn(t_map *map, char spawn, int amount)
{
	int	x;
	int	y;

	while (amount--)
	{
		x = 1 + 2 * (rand() % ((map->height - 1) / 2));
		y = 1 + 2 * (rand() % ((map->width - 1) / 2));
		while (map->map[x][y] != PATH)
		{
			x = 1 + 2 * (rand() % ((map->height - 1) / 2));
			y = 1 + 2 * (rand() % ((map->width - 1) / 2));
		}
		map->map[x][y] = spawn;
	}
}

void	ft_generate_map(t_data *data)
{
	ft_seed(&data->input);
	ft_set_map(data);
	ft_make_grid_map(data);
	if (data->map.height % 2 == 0)
		ft_add_spikes(&data->map, data->map.height - 2, 1);
	if (data->map.width % 2 == 0)
		ft_add_spikes(&data->map, 1, data->map.width - 2);
	ft_generate_maze(&data->map);
	ft_spawn(&data->map, PLAYER, 1);
	ft_spawn(&data->map, EXIT, 1);
	ft_spawn(&data->map, COLLECTIBLE, data->map.collects);
	ft_spawn(&data->map, ENEMY, data->map.enemies);
}
