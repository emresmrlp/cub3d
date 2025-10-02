/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:09:09 by ysumeral          #+#    #+#             */
/*   Updated: 2025/10/02 13:13:28 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/memory.h"

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
			// YSUMERAL: Destroy the display and free the mlx pointer beacause it was allocated by mlx_init() function
			mlx_destroy_display(game->mlx);
			free(game->mlx);
			game->mlx = NULL;
		}
		free(game);
		game = NULL;
	}
}
