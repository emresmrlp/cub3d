/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:43:50 by ysumeral          #+#    #+#             */
/*   Updated: 2025/10/02 15:53:36 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include <stdio.h>
# include <stdlib.h>
# include "../mlx/mlx.h"
# define SIZE_X 1024
# define SIZE_Y 512

typedef struct s_texture
{
	int ceiling_color[3];
	int floor_color[3];
	int x;
	int y;
	void *no_wall;
	void *so_wall;
	void *we_wall;
	void *ea_wall;
}	t_texture;

typedef struct s_game 
{
	void *mlx;
	void *win;
	t_texture texture;
}	t_game;

void init(t_game *game);
void start(t_game *game);
void quit(t_game *game);
void fatal_quit(t_game *game);

#endif