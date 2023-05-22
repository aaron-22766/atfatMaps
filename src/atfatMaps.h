/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atfatMaps.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:14:41 by arabenst          #+#    #+#             */
/*   Updated: 2023/05/22 11:50:54 by arabenst         ###   ########.fr       */
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
# include <string.h>
# include <sys/errno.h>
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
# define UNVISITED ' '

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
	ERR_ARG_DUPLICATE,
	ERR_TOO_SMALL,
	ERR_INVALID_PATH
};

/* ************************************************************************** */
/*                                  STRUCTS                                   */
/* ************************************************************************** */

typedef struct s_map
{
	int		width;
	int		height;
	int		collects;
	int		enemies;
	char	**map;
}	t_map;

typedef struct s_input
{
	bool	help;
	bool	verbose;
	bool	random_seed;
	t_map	map_input;
	char	*file;
	char	*seed;
	char	*path;
	char	*invalid;
}	t_input;

typedef struct s_data
{
	t_input	input;
	t_map	map;
}	t_data;

/* ************************************************************************** */
/*                                 FUNCTIONS                                  */
/* ************************************************************************** */

// atfatMaps.c
char		**atfatmaps(int argc, char **argv);

// init.c
void		ft_init_data(t_data *data);

// input.c
void		ft_get_input(t_input *input, int argc, char **argv);

// get_map.c
void		ft_get_map(t_data *data);

// seed.c
void		ft_seed(t_input *input);

// generate_map.c
void		ft_generate_map(t_data *data);

// generate_maze.c
void		ft_generate_maze(t_map *map);

// invalid.c
void		ft_apply_invalid(t_data *data);

// error.c
void		ft_error(char err);

// free.c
void		ft_free_map(char **map);
void		ft_free_seed(t_input *input);
void		ft_ferror(t_data *data, char err);

// utils.c
void		ft_print_map(char **map);

#endif
