/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 05:30:00 by zkayadib          #+#    #+#             */
/*   Updated: 2025/11/27 15:58:10 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/input.h"

static void	set_player_direction_for_we(t_game *game, char direction)
{
	if (direction == 'E')
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = 0.66;
	}
	else if (direction == 'W')
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = -0.66;
	}
}

static void	set_player_direction(t_game *game, char direction)
{
	if (direction == 'N')
	{
		game->player.dir_x = 0;
		game->player.dir_y = -1;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0;
	}
	else if (direction == 'S')
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
		game->player.plane_x = -0.66;
		game->player.plane_y = 0;
	}
	else
		set_player_direction_for_we(game, direction);
}

void	init_player(t_game *game)
{
	char	player;

	game->player.pos_x = (double)game->player_x + 0.5;
	game->player.pos_y = (double)game->player_y + 0.5;
	player = game->map.map[game->player_y][game->player_x];
	set_player_direction(game, player);
	game->player.move_speed = 0.08;
	game->player.rot_speed = 0.04;
	game->player.key_w = 0;
	game->player.key_s = 0;
	game->player.key_a = 0;
	game->player.key_d = 0;
	game->player.key_left = 0;
	game->player.key_right = 0;
	game->last_frame_time = calc_time();
}
