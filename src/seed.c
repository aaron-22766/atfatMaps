/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seed.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 09:40:40 by arabenst          #+#    #+#             */
/*   Updated: 2023/05/11 12:57:42 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atfatMaps.h"

static void	ft_get_random_seed(t_input *input)
{
	struct timespec	ts;
	char			*chars;
	int				i;
	int				len;

	timespec_get(&ts, TIME_UTC);
	srand(ts.tv_nsec);
	len = 1 + rand() % 50;
	input->seed = ft_calloc(len + 1, sizeof(char));
	if (!input->seed)
		ft_error(ERR_MEM);
	chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	i = -1;
	while (++i < len)
		input->seed[i] = chars[rand() % 62];
}

static void	ft_set_seed(t_input *input)
{
	unsigned int	seed;
	size_t			i;

	srand(42);
	seed = 0;
	i = -1;
	while (input->seed[++i])
		seed += input->seed[i] * rand();
	srand(seed);
}

static void	ft_set_input(t_input *input)
{
	if (!input->width)
		input->width = 5 + rand() % 35;
	if (!input->height)
		input->height = 5 + rand() % 35;
	if (!input->collects)
		input->collects = 1 + rand() % ft_sqrt(input->width * input->height);
	if (!input->enemies)
		input->enemies = rand() % (ft_sqrt(input->width * input->height) - 4);
}

void	ft_seed(t_input *input)
{
	if (input->random_seed)
		ft_get_random_seed(input);
	ft_set_seed(input);
	ft_set_input(input);
}
