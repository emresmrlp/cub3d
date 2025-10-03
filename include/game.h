/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:43:50 by ysumeral          #+#    #+#             */
/*   Updated: 2025/10/03 16:46:19 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include <stdio.h>
# include <stdlib.h>
# include "../external/gnl/get_next_line.h"
# include "../external/mlx/mlx.h"
# define SIZE_X 1024
# define SIZE_Y 512
# define TRUE 1
# define FALSE 0

typedef struct s_texture
{
	int ceiling_color[3];
	int floor_color[3];
	int x;
	int y;
	int img_height;
	int img_width;
	void *no_wall;
	char *no_path;
	void *so_wall;
	char *so_path;
	void *we_wall;
	char *we_path;
	void *ea_wall;
	char *ea_path;
	void *background;
	char *addr;
	int bits_pixel;
	int x_byte;
	int endian;
}	t_texture;

typedef struct s_map
{
	char	**map;
	char	**map_copy;
	int		size_x;
	int		size_y;
}	t_map;

typedef struct s_game 
{
	void		*mlx;
	void		*win;
	t_texture	texture;
	t_map		map;
}	t_game;

void	start(t_game *game);
void	quit(t_game *game);
void	fatal_quit(t_game *game);

#endif