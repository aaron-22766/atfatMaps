/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 09:32:15 by arabenst          #+#    #+#             */
/*   Updated: 2023/05/15 10:57:22 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atfatMaps.h"

void	ft_init_map(t_map *map)
{
	map->width = -1;
	map->height = -1;
	map->collects = -1;
	map->enemies = -1;
	map->map = NULL;
}

void	ft_init_input(t_input *input)
{
	ft_init_map(&input->map_input);
	input->help = false;
	input->verbose = false;
	input->random_seed = false;
	input->file = NULL;
	input->seed = NULL;
	input->path = NULL;
	input->invalid = NULL;
}
