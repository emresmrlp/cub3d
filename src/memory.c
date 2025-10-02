/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:09:09 by ysumeral          #+#    #+#             */
/*   Updated: 2025/10/02 19:32:58 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/memory.h"

static void cleanup_texture(t_game *game)
{
	if (game->texture.no_wall)
		mlx_destroy_image(game->mlx, game->texture.no_wall);
	if (game->texture.we_wall)
		mlx_destroy_image(game->mlx, game->texture.we_wall);
	if (game->texture.ea_wall)
		mlx_destroy_image(game->mlx, game->texture.ea_wall);
	if (game->texture.so_wall)
		mlx_destroy_image(game->mlx, game->texture.so_wall);
}

void cleanup(t_game *game)
{
	if (game)
	{
		if (game->win)
		{
			// YSUMERAL: Destroy the window but do not free the pointer directly because it is managed by the MLX library
			mlx_destroy_window(game->mlx, game->win);
			game->win = NULL;
		}
		if (game->mlx)
		{
			cleanup_texture(game);
			// YSUMERAL: Destroy the display and free the mlx pointer beacause it was allocated by mlx_init() function
			mlx_destroy_display(game->mlx);
			free(game->mlx);
			game->mlx = NULL;
		}
		free(game);
		game = NULL;
	}
}
