/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_maze.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:52:13 by arabenst          #+#    #+#             */
/*   Updated: 2023/05/22 11:44:29 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atfatMaps.h"

static bool	ft_choords_out_of_bounds(t_map *map, int x, int y)
{
	return (x < 1 || x > map->height - 2 || y < 1 || y > map->width - 2);
}

static void	ft_draw_position(t_map *map, int x, int y, char origin)
{
	map->map[x][y] = PATH;
	if (origin == 2)
		map->map[x - 1][y] = PATH;
	if (origin == 3)
		map->map[x][y + 1] = PATH;
	if (origin == 0)
		map->map[x + 1][y] = PATH;
	if (origin == 1)
		map->map[x][y - 1] = PATH;
}

static void	ft_recursive_dfs(t_map *map, int x, int y, char origin)
{
	char	dir;
	char	i;

	if (ft_choords_out_of_bounds(map, x, y) || map->map[x][y] != UNVISITED)
		return ;
	ft_draw_position(map, x, y, origin);
	dir = rand() % 4;
	i = -1;
	while (++i < 4)
	{
		if (dir == 0)
			ft_recursive_dfs(map, x - 2, y, dir);
		if (dir == 1)
			ft_recursive_dfs(map, x, y + 2, dir);
		if (dir == 2)
			ft_recursive_dfs(map, x + 2, y, dir);
		if (dir == 3)
			ft_recursive_dfs(map, x, y - 2, dir);
		dir = (dir + 1) % 4;
	}
}

void	ft_generate_maze(t_map *map)
{
	ft_recursive_dfs(map,
		1 + 2 * (rand() % (map->height / 2 - !(map->height % 2))),
		1 + 2 * (rand() % (map->width / 2 - !(map->width % 2))), -1);
}
