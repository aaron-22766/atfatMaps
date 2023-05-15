/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:09:33 by arabenst          #+#    #+#             */
/*   Updated: 2023/05/15 11:49:56 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atfatMaps.h"

void	ft_print_map(char **map)
{
	int	i;

	if (!map)
	{
		ft_printf("Ooops! Somehow the map got corrupted!\n");
		return ;
	}
	i = -1;
	while (map[++i])
		ft_printf("%s\n", map[i]);
}
