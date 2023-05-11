/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:06:58 by arabenst          #+#    #+#             */
/*   Updated: 2023/05/11 15:28:26 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atfatMaps.h"

static char	**ft_make_walled_map(t_input *input)
{
	char	**map;
	int		i;

	map = ft_calloc(input->height + 1, sizeof(char *));
	if (!map)
		ft_ferror(input, map, ERR_MEM);
	i = -1;
	while (++i < input->height)
	{
		map[i] = ft_calloc(input->width + 1, sizeof(char));
		if (!map[i])
			ft_ferror(input, map, ERR_MEM);
		ft_memset(map[i], WALL, input->width);
	}
	return (map);
}

static void	ft_spawn(t_input *input, char **map, char spawn, int amount)
{
	(void)input;
	(void)map;
	(void)spawn;
	(void)amount;
}

char	**ft_generate_map(t_input *input)
{
	char	**map;

	ft_seed(input);
	map = ft_make_walled_map(input);
	ft_generate_maze(input, map);
	ft_spawn(input, map, PLAYER, 1);
	ft_spawn(input, map, EXIT, 1);
	ft_spawn(input, map, COLLECTIBLE, input->collects);
	ft_spawn(input, map, ENEMY, input->enemies);
	return (map);
}
