/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:53:08 by arabenst          #+#    #+#             */
/*   Updated: 2023/05/17 15:35:55 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atfatMaps.h"

static bool	ft_get_optional_flag(t_input *input, char *arg, char *next_arg)
{
	if (arg[0] != '-')
		return (false);
	arg++;
	if ((!ft_strcmp(arg, "h") || !ft_strcmp(arg, "-help"))
		&& (!next_arg || next_arg[0] == '-'))
	{
		input->help = true;
		return (true);
	}
	else if (!ft_strcmp(arg, "v") || !ft_strcmp(arg, "-verbose"))
	{
		input->verbose = true;
		return (true);
	}
	return (false);
}

static void	ft_get_map_flags(t_input *input, char flag, char *next_arg)
{
	int	n;

	if (!next_arg || next_arg[0] == '-')
		ft_error(flag);
	n = ft_atoi(next_arg);
	if (n > 255 || (ft_strchr("wh", flag) && n < 3)
		|| (flag == 'c' && n < 1) || (flag == 'e' && n < 0))
		ft_error(flag);
	if ((flag == 'w' && input->map_input.width != -1)
		|| (flag == 'h' && input->map_input.height != -1)
		|| (flag == 'c' && input->map_input.collects != -1)
		|| (flag == 'e' && input->map_input.enemies != -1))
		ft_error(ERR_ARG_DUPLICATE);
	if (flag == 'w')
		input->map_input.width = n;
	else if (flag == 'h')
		input->map_input.height = n;
	else if (flag == 'c')
		input->map_input.collects = n;
	else if (flag == 'e')
		input->map_input.enemies = n;
}

static void	ft_get_string_flags(t_input *input, char flag, char *next_arg)
{
	if (!next_arg || next_arg[0] == '-')
		ft_error(flag);
	if ((flag == 'p' && input->path) || (flag == 's' && input->seed)
		|| (flag == 'i' && input->invalid))
		ft_error(ERR_ARG_DUPLICATE);
	if (flag == 'p')
	{
		if (!ft_strnstr(next_arg, ".ber", ft_strlen(next_arg))
			&& next_arg[ft_strlen(next_arg) - 1] != '/')
			ft_error(ERR_INVALID_PATH);
		input->path = next_arg;
	}
	else if (flag == 's')
		input->seed = next_arg;
	else if (flag == 'i')
	{
		if (!ft_strcmp(next_arg, "IE")
			|| (next_arg[0] == 'E' && ft_strchr("FLPEC", next_arg[1]))
			|| (next_arg[0] == 'N' && ft_strchr("RWP", next_arg[1]))
			|| (next_arg[0] == 'M' && ft_strchr("PEC", next_arg[1])))
			input->invalid = next_arg;
		else
			ft_error(flag);
	}
}

static bool	ft_get_flag(t_input *input, char *arg, char *next_arg)
{
	if (arg[0] != '-')
		return (false);
	arg++;
	if (!ft_strcmp(arg, "w") || !ft_strcmp(arg, "-width"))
		return (ft_get_map_flags(input, 'w', next_arg), true);
	else if (!ft_strcmp(arg, "h") || !ft_strcmp(arg, "-height"))
		return (ft_get_map_flags(input, 'h', next_arg), true);
	else if (!ft_strcmp(arg, "c") || !ft_strcmp(arg, "-collectibles"))
		return (ft_get_map_flags(input, 'c', next_arg), true);
	else if (!ft_strcmp(arg, "e") || !ft_strcmp(arg, "-enemies"))
		return (ft_get_map_flags(input, 'e', next_arg), true);
	else if (!ft_strcmp(arg, "p") || !ft_strcmp(arg, "-path"))
		return (ft_get_string_flags(input, 'p', next_arg), true);
	else if (!ft_strcmp(arg, "s") || !ft_strcmp(arg, "-seed"))
		return (ft_get_string_flags(input, 's', next_arg), true);
	else if (!ft_strcmp(arg, "i") || !ft_strcmp(arg, "-invalid"))
		return (ft_get_string_flags(input, 'i', next_arg), true);
	return (false);
}

void	ft_get_input(t_input *input, int argc, char **argv)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (ft_get_optional_flag(input, argv[i], argv[i + 1]))
			continue ;
		if (ft_get_flag(input, argv[i], argv[i + 1]))
			i++;
		else
		{
			if (input->file)
				ft_error(ERR_ARG_DUPLICATE);
			input->file = argv[i];
		}
	}
	if (input->file && (input->path || input->seed || input->invalid
			|| input->map_input.width != -1 || input->map_input.height != -1
			|| input->map_input.collects != -1
			|| input->map_input.enemies != -1))
		ft_error(ERR_ARG_MIXED);
	if (input->map_input.width > 0 && input->map_input.height > 0
		&& input->map_input.width * input->map_input.height <= 14)
		ft_error(ERR_TOO_SMALL);
	input->random_seed = !input->seed;
}
