/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:41:42 by arabenst          #+#    #+#             */
/*   Updated: 2023/05/11 10:25:18 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atfatMaps.h"

int	main(int argc, char **argv)
{
	char	**map;
	int		i;

	map = atfatmaps(argc, argv);
	ft_print_map(map);
	i = 0;
	while (++i < argc)
	{
		if (!ft_strcmp(argv[i], "-v") || !ft_strcmp(argv[i], "--verbose"))
		{
			ft_printf("\n");
			break ;
		}
	}
	ft_free_map(map);
	return (RETURN_SUCCESS);
}
