/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 09:25:59 by arabenst          #+#    #+#             */
/*   Updated: 2023/05/22 11:44:13 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atfatMaps.h"

void	ft_free_map(char **map)
{
	int	i;

	i = -1;
	while (map && map[++i])
		free(map[i]);
	free(map);
}

void	ft_free_seed(t_input *input)
{
	if (input->random_seed)
		free(input->seed);
}

void	ft_ferror(t_data *data, char err)
{
	ft_free_map(data->map.map);
	ft_free_seed(&data->input);
	ft_error(err);
}
