/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atfatMaps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:14:29 by arabenst          #+#    #+#             */
/*   Updated: 2023/05/15 11:03:04 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atfatMaps.h"

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

static void	ft_verbose_mode(t_data *data, char *exe_name)
{
	if (data->input.file)
		ft_printf("\nRead map from file: %s\n\n", data->input.file);
	else
		ft_printf("\nGenerated map from seed: %s\n\n", data->input.seed);
	ft_printf("Specs:\n%d x %d (w x h)\n", data->map.width, data->map.height);
	if (data->map.collects == 1)
		ft_printf("1 collectible\n");
	else
		ft_printf("%d collectibles\n", data->map.collects);
	if (data->map.enemies == 1)
		ft_printf("1 enemy\n\n");
	else
		ft_printf("%d enemies\n\n", data->map.enemies);
	if (!ft_strnstr(exe_name, "/atfatMaps", ft_strlen(exe_name)))
	{
		ft_print_map(data->map.map);
		ft_printf("\n");
	}
}

char	**atfatmaps(int argc, char **argv)
{
	t_data	data;

	ft_init_input(&data.input);
	ft_get_input(&data.input, argc, argv);
	if (data.input.help)
		ft_print_help();
	if (data.input.file)
		ft_get_map(&data);
	else
		ft_generate_map(&data);
	if (data.input.verbose)
		ft_verbose_mode(&data, argv[0]);
	return (ft_free_seed(&data.input), data.map.map);
}
