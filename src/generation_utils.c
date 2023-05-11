/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:59:44 by arabenst          #+#    #+#             */
/*   Updated: 2023/05/11 15:17:01 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atfatMaps.h"

bool	ft_pos_has_walls(t_input *input, char **map, int min_walls, int pos)
{
	int	i;
	int	j;

	i = pos / input->width;
	j = pos % input->width;
	return ((map[i + 1][j] == WALL) + (map[i - 1][j] == WALL) +
		(map[i][j + 1] == WALL) + (map[i][j - 1] == WALL) >= min_walls);
}

int	ft_count_pos_with_walls(t_input *input, char **map, int min_walls)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (map[++i + 1])
	{
		j = 0;
		while (map[i][++j + 1])
			if (ft_pos_has_walls(input, map, min_walls, i * input->width + j))
				count++;
	}
	return (count);
}

int	ft_get_random_pos(t_input *input, char **map, int min_walls)
{
	int	*wall_pos;
	int	count;
	int	w;
	int	i;
	int	j;

	count = ft_count_pos_with_walls(map, min_walls);
	if (count < 1)
		return (-1);
	wall_pos = malloc(count * sizeof(int));
	if (!wall_pos)
		ft_ferror(input, map, ERR_MEM);
	w = 0;
	i = 0;
	while (map[++i + 1])
	{
		j = 0;
		while (map[i][++j + 1])
			if ((map[i + 1][j] == WALL) + (map[i - 1][j] == WALL) +
				(map[i][j + 1] == WALL) + (map[i][j - 1] == WALL) >= min_walls)
				wall_pos[w++] = i * input->width + j;
	}
	w = wall_pos[rand() % count];
	free(wall_pos);
	return (w);
}
