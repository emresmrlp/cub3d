/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:43:50 by ysumeral          #+#    #+#             */
/*   Updated: 2025/10/02 19:06:55 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include <stdio.h>
# include <stdlib.h>
# include "../mlx/mlx.h"
# define SIZE_X 3000
# define SIZE_Y 1500

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
}	t_texture;

typedef struct s_game 
{
	void *mlx;
	void *win;
	t_texture texture;
}	t_game;

void start(t_game *game);
void quit(t_game *game);
void fatal_quit(t_game *game);

#endif