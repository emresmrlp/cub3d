/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 18:49:16 by ysumeral          #+#    #+#             */
/*   Updated: 2025/11/22 17:58:41 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/init.h"

static void	init_param(t_game *game)
{
	game->texture.background = mlx_new_image(game->mlx, SIZE_X, SIZE_Y);
	if (!game->texture.background)
		fatal_quit(game, "Background init failed.");
	game->texture.addr = mlx_get_data_addr(game->texture.background,
			&game->texture.bits_pixel, &game->texture.x_byte,
			&game->texture.endian);
	if (!game->texture.addr)
		fatal_quit(game, "Background init failed.");
	game->texture.img_height = 64;
	game->texture.img_width = 64;
	game->texture.x = 0;
	game->texture.y = 0;
}

static void	init_texture(t_game *game)
{
	game->texture.no_wall = mlx_xpm_file_to_image(game->mlx,
			game->texture.no_path, &game->texture.img_width,
			&game->texture.img_height);
	if (!game->texture.no_wall)
		fatal_quit(game, "North wall upload failed.");
	game->texture.we_wall = mlx_xpm_file_to_image(game->mlx,
			game->texture.we_path, &game->texture.img_width,
			&game->texture.img_height);
	if (!game->texture.we_wall)
		fatal_quit(game, "West wall upload failed.");
	game->texture.so_wall = mlx_xpm_file_to_image(game->mlx,
			game->texture.so_path, &game->texture.img_width,
			&game->texture.img_height);
	if (!game->texture.so_wall)
		fatal_quit(game, "South wall upload failed.");
	game->texture.ea_wall = mlx_xpm_file_to_image(game->mlx,
			game->texture.ea_path, &game->texture.img_width,
			&game->texture.img_height);
	if (!game->texture.ea_wall)
		fatal_quit(game, "East wall upload failed.");
}

void	init(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		fatal_quit(game, "MLX init failed.");
	game->win = mlx_new_window(game->mlx, SIZE_X, SIZE_Y, "DEEP THOUGHT MAZE");
	if (!game->win)
		fatal_quit(game, "Window init failed.");
	init_param(game);
	init_texture(game);
	init_player(game);
}
