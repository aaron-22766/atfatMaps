/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atfatMaps.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:14:41 by arabenst          #+#    #+#             */
/*   Updated: 2023/05/11 15:18:29 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ATFATMAPS_H
# define ATFATMAPS_H

/* ************************************************************************** */
/*                                  INCLUDES                                  */
/* ************************************************************************** */

# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <time.h>
# include "../lib/libft/libft.h"

/* ************************************************************************** */
/*                                  DEFINES                                   */
/* ************************************************************************** */

# define PATH '0'
# define WALL '1'
# define PLAYER 'P'
# define COLLECTIBLE 'C'
# define EXIT 'X'
# define ENEMY 'E'

# define RETURN_SUCCESS 0
# define RETURN_FAILURE 1

/* ************************************************************************** */
/*                                   ENUMS                                    */
/* ************************************************************************** */

enum e_errors
{
	ERR_MEM,
	ERR_READ_FROM_FILE,
	ERR_ARG_MIXED,
	ERR_ARG_DUPLICATE
};

/* ************************************************************************** */
/*                                  STRUCTS                                   */
/* ************************************************************************** */

typedef struct s_input
{
	bool			help;
	bool			verbose;
	bool			random_seed;
	unsigned char	width;
	unsigned char	height;
	unsigned char	collects;
	unsigned char	enemies;
	char			*file;
	char			*seed;
	char			*path;
	char			*invalid;
}	t_input;

/* ************************************************************************** */
/*                                 FUNCTIONS                                  */
/* ************************************************************************** */

// atfatMaps.c
char		**atfatmaps(int argc, char **argv);

// input.c
void		ft_get_input(t_input *input, int argc, char **argv);

// get_map.c
char		**ft_get_map(char *path);

// seed.c
void		ft_seed(t_input *input);

// generate_map.c
char		**ft_generate_map(t_input *input);

// generate_maze.c
void		ft_generate_maze(t_input *input, char **map);

// generation_utils.c
bool		ft_pos_has_walls(t_input *input, char **map, int min_walls,
				int pos);
int			ft_count_pos_with_walls(t_input *input, char **map, int min_walls);
int			ft_get_random_pos(t_input *input, char **map, int min_walls);

// ferror.c
void		ft_error(char err);
void		ft_free_map(char **map);
void		ft_free_seed(t_input *input);
void		ft_ferror(t_input *input, char **map, char err);

// utils.c
void		ft_print_map(char **map);

#endif
