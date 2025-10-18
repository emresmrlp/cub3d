/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 18:49:16 by ysumeral          #+#    #+#             */
/*   Updated: 2025/10/18 17:01:19 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/init.h"

static void init_param(t_game *game)
{
	game->texture.background = mlx_new_image(game->mlx, SIZE_X, SIZE_Y);
	if (!game->texture.background)
		fatal_quit(game);
	game->texture.addr = mlx_get_data_addr(game->texture.background, &game->texture.bits_pixel, &game->texture.x_byte, &game->texture.endian);
	if (!game->texture.addr)
		fatal_quit(game);
	game->texture.img_height = 64;
	game->texture.img_width = 64;
	game->texture.x = 0;
	game->texture.y = 0;
}

static void init_texture(t_game *game)
{
	game->texture.no_wall = mlx_xpm_file_to_image(game->mlx,
		game->texture.no_path, &game->texture.img_width,
		&game->texture.img_height);
	if (!game->texture.no_wall)
		(fatal_debug("NORTH WALL CANT UPLOAD"), fatal_quit(game));
	game->texture.we_wall = mlx_xpm_file_to_image(game->mlx,
		game->texture.we_path, &game->texture.img_width,
		&game->texture.img_height);
	if (!game->texture.we_wall)
		(fatal_debug("WEST WALL CANT UPLOAD"), fatal_quit(game));
	game->texture.so_wall = mlx_xpm_file_to_image(game->mlx,
		game->texture.so_path, &game->texture.img_width,
		&game->texture.img_height);
	if (!game->texture.so_wall)
		(fatal_debug("SOUTH WALL CANT UPLOAD"), fatal_quit(game));
	game->texture.ea_wall = mlx_xpm_file_to_image(game->mlx,
		game->texture.ea_path, &game->texture.img_width,
		&game->texture.img_height);
	if (!game->texture.ea_wall)
		(fatal_debug("EAST WALL CANT UPLOAD"), fatal_quit(game));
}

void init(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		fatal_debug("mlx init failed!");
	game->win = mlx_new_window(game->mlx, SIZE_X, SIZE_Y, "DEEP THOUGHT MAZE");
	if (!game->win)
		fatal_debug("window init failed!");
	init_param(game);
	init_texture(game);
}