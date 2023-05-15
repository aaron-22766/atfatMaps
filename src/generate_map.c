/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:06:58 by arabenst          #+#    #+#             */
/*   Updated: 2023/05/15 11:26:44 by arabenst         ###   ########.fr       */
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
		% (ft_sqrt(data->map.width * data->map.height) - 4);
	if (data->input.map_input.enemies != -1)
		data->map.enemies = data->input.map_input.enemies;
}

static void	ft_make_walled_map(t_data *data)
{
	int	i;

	data->map.map = ft_calloc(data->map.height + 1, sizeof(char *));
	if (!data->map.map)
		ft_ferror(data, ERR_MEM);
	i = -1;
	while (++i < data->map.height)
	{
		data->map.map[i] = ft_calloc(data->map.width + 1, sizeof(char));
		if (!data->map.map[i])
			ft_ferror(data, ERR_MEM);
		ft_memset(data->map.map[i], WALL, data->map.width);
	}
}

static void	ft_spawn(t_map *map, char spawn, int amount)
{
	(void)map;
	(void)spawn;
	(void)amount;
}

void	ft_generate_map(t_data *data)
{
	ft_seed(&data->input);
	ft_set_map(data);
	ft_make_walled_map(data);
	ft_generate_maze(data);
	ft_spawn(&data->map, PLAYER, 1);
	ft_spawn(&data->map, EXIT, 1);
	ft_spawn(&data->map, COLLECTIBLE, data->map.collects);
	ft_spawn(&data->map, ENEMY, data->map.enemies);
}
