/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_maze.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:52:13 by arabenst          #+#    #+#             */
/*   Updated: 2023/05/11 15:29:08 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atfatMaps.h"

static void	ft_walk_path(t_input *input, char **map, int pos)
{
	int	dir;

	if (!ft_pos_has_walls(input, map, 4, pos))
		return ;
	map[pos / input->width][pos % input->width] = PATH;
	dir = rand() % 4
	
	// CHECK FOR EDGE

	if (dir == 0)
		ft_walk_path(input, map, pos - input->width);
	else if (dir == 1)
		ft_walk_path(input, map, pos - input->width);
	else if (dir == 2)
		ft_walk_path(input, map, pos - input->width);
	else
		ft_walk_path(input, map, pos - input->width);
}

void	ft_generate_maze(t_input *input, char **map)
{
	int	pos;

	while (1)
	{
		pos = ft_get_random_postion(input, map, 4);
		if (pos == -1)
			break ;
		ft_walk_path(input, map, pos);
	}
}
