/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 08:59:12 by arabenst          #+#    #+#             */
/*   Updated: 2023/05/22 11:44:49 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atfatMaps.h"

static void	ft_puterror(const char *fault, const char *expectation)
{
	if (fault && ft_strlen(fault))
		ft_printf("\nERROR! (atfatMap)\n%s", fault);
	if (expectation && ft_strlen(expectation))
		ft_printf(" Expected: %s", expectation);
	ft_printf("\n\n");
	exit(EXIT_FAILURE);
}

static void	ft_flag_errors(char err)
{
	if (err == 'w')
		ft_puterror("Invalid argument for 'width'!", "(3 - 255)");
	else if (err == 'h')
		ft_puterror("Invalid argument for 'height'!", "(3 - 255)");
	else if (err == 'c')
		ft_puterror("Invalid argument for 'collectibles'!", "(1 - 255)");
	else if (err == 'e')
		ft_puterror("Invalid argument for 'enemies'!", "(0 - 255)");
	else if (err == 's')
		ft_puterror("No seed specified!", "");
	else if (err == 'p')
		ft_puterror("No path specified!", "");
	else if (err == 'i')
		ft_puterror("Invalid (-i) INVALID_CODE!",
			"[IE, EF, EL, NR, NW, NP, MP, ME, MC, EP, EE, EC]");
}

void	ft_error(char err)
{
	if (err == ERR_MEM)
		ft_puterror("Memory allocation failed!", "");
	else if (err == ERR_READ_FROM_FILE)
		ft_puterror("Failed reading from file!", "");
	else if (err == ERR_ARG_MIXED)
		ft_puterror("Mixed arguments!",
			"[file] exclusively! Opionals [-h], [-v] allowed.");
	else if (err == ERR_ARG_DUPLICATE)
		ft_puterror("Duplicate arguments!", "");
	else if (err == ERR_TOO_SMALL)
		ft_puterror("Map too small!", "(width * height > 14)");
	else if (err == ERR_INVALID_PATH)
		ft_puterror("Invalid argument for 'path'!",
			"Directory or file name ending in '.ber'");
	else
		ft_flag_errors(err);
}
