/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atfatMaps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:14:29 by arabenst          #+#    #+#             */
/*   Updated: 2023/05/22 11:49:56 by arabenst         ###   ########.fr       */
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
	ft_printf("Specs:\n%d x %d (h x w)\n", data->map.height, data->map.width);
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

static char	*ft_get_path(t_data *data)
{
	size_t	len;
	char	*path;

	len = ft_strlen(data->input.path);
	if (data->input.path[len - 1] == '/')
	{
		len += ft_strlen(data->input.seed) + 5;
		path = ft_calloc(len, sizeof(char));
		if (!path)
			ft_ferror(data, ERR_MEM);
		ft_strcpy(path, data->input.path);
		ft_strlcat(path, data->input.seed, len);
		ft_strlcat(path, ".ber", len);
		return (path);
	}
	return (data->input.path);
}

static void	ft_save_to_file(t_data *data)
{
	char	*path;
	int		fd;
	int		i;

	path = ft_get_path(data);
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		if (ft_strcmp(path, data->input.path))
			free(path);
		ft_printf("\nERROR! (atfatMap)\nFailed to open file: %s\n\n",
			strerror(errno));
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (++i < data->map.height)
	{
		ft_putstr_fd(data->map.map[i], fd);
		ft_putchar_fd('\n', fd);
	}
	close(fd);
}

char	**atfatmaps(int argc, char **argv)
{
	t_data	data;

	ft_init_data(&data);
	ft_get_input(&data.input, argc, argv);
	if (data.input.help)
		ft_print_help();
	if (data.input.file)
		ft_get_map(&data);
	else
		ft_generate_map(&data);
	if (data.input.verbose)
		ft_verbose_mode(&data, argv[0]);
	if (data.input.path)
		ft_save_to_file(&data);
	if (data.input.invalid)
		ft_apply_invalid(&data);
	return (ft_free_seed(&data.input), data.map.map);
}
