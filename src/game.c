/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:10:47 by ysumeral          #+#    #+#             */
/*   Updated: 2025/10/02 15:55:05 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game.h"
#include "../include/memory.h"
#include "../include/debugger.h"

void init(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		fatal_debug("mlx init failed!");
	game->win = mlx_new_window(game->mlx, SIZE_X, SIZE_Y, "DEEP THOUGHT MAZE");
	if (!game->win)
		fatal_debug("window init failed!");
}

void start(t_game *game)
{
	debug("start function");
	mlx_loop(game->mlx);
}

void quit(t_game *game)
{
	debug("quit function");
	cleanup(game);
	exit(0);
}

void fatal_quit(t_game *game)
{
	fatal_debug("fatal quit function");
	cleanup(game);
	exit(1);
}
