/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atfatMaps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:14:29 by arabenst          #+#    #+#             */
/*   Updated: 2023/05/11 12:36:25 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atfatMaps.h"

static void	ft_init_input(t_input *input)
{
	input->help = false;
	input->verbose = false;
	input->random_seed = false;
	input->width = 0;
	input->height = 0;
	input->collects = 0;
	input->enemies = 0;
	input->file = NULL;
	input->seed = NULL;
	input->path = NULL;
	input->invalid = NULL;
}

static void	ft_print_help(void)
{
	int		fd;
	char	*line;

	fd = open("help.txt", O_RDONLY);
	if (fd == -1)
		ft_error(ERR_READ_FROM_FILE);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		ft_putstr_fd(line, STDOUT_FILENO);
		free(line);
	}
	close(fd);
	exit(EXIT_SUCCESS);
}

static void	ft_measure_map(t_input *input, char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == COLLECTIBLE)
				input->collects++;
			else if (map[i][j] == ENEMY)
				input->enemies++;
		}
		if (j > input->width)
			input->width = j;
	}
	input->height = i;
}

static void	ft_verbose_mode(t_input *input, char **map, char *exe_name)
{
	if (input->file)
	{
		ft_printf("\nRead map from file: %s\n\n", input->file);
		ft_measure_map(input, map);
	}
	else
		ft_printf("\nGenerated map from seed: %s\n\n", input->seed);
	ft_printf("Specs:\n%d x %d (w x h)\n", input->width, input->height);
	if (input->collects == 1)
		ft_printf("1 collectible\n");
	else
		ft_printf("%d collectibles\n", input->collects);
	if (input->enemies == 1)
		ft_printf("1 enemy\n\n");
	else
		ft_printf("%d enemies\n\n", input->enemies);
	if (!ft_strnstr(exe_name, "/atfatMaps", ft_strlen(exe_name)))
	{
		ft_print_map(map);
		ft_printf("\n");
	}
}

char	**atfatmaps(int argc, char **argv)
{
	t_input	input;
	char	**map;

	ft_init_input(&input);
	ft_get_input(&input, argc, argv);
	if (input.help)
		ft_print_help();
	if (input.file)
		map = ft_get_map(input.file);
	else
		map = ft_generate_map(&input);
	if (input.verbose)
		ft_verbose_mode(&input, map, argv[0]);
	return (ft_free_seed(&input), map);
}
