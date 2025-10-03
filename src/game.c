/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:10:47 by ysumeral          #+#    #+#             */
/*   Updated: 2025/10/03 13:38:18 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game.h"
#include "../include/memory.h"
#include "../include/debugger.h"
#include "../include/draw.h"

void start(t_game *game)
{
	debug("start function");
	draw_background(game);
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
