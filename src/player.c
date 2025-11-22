/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zulfiye <zulfiye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 05:30:00 by zulfiye           #+#    #+#             */
/*   Updated: 2025/11/22 15:32:44 by zulfiye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/init.h"
#include "../include/input.h"
#include <math.h>
#include <sys/time.h>

//dir tek bir konumu ele aldığı için, yalnızca ekranın ortasını görebilirdik
//yelpaze görünümü için plane'e ihtiyaç duyarız
static void	set_direction(t_game *game, double dir_x,
	double dir_y, double plane_x, double plane_y)
{
	game->player.dir_x = dir_x;
	game->player.dir_y = dir_y;
	game->player.plane_x = plane_x;
	game->player.plane_y = plane_y;
}

static void set_player_direction(t_game *game, char direction)
{
	if (direction == 'E')
		set_direction(game, 1, 0, 0, 0.66);
	else if (direction == 'W')
		set_direction(game, -1, 0, 0, -0.66);
	else if (direction == 'N')
		set_direction(game, 0, -1, 0.66, 0);
	else if (direction == 'S')
		set_direction(game, 0, 1, -0.66, 0);
}

void init_player(t_game *game)
{
	char player;
	
	// Amaç player pozisyonunu +0.5 ekleyerek hücrenin tam ortasına yerleştirmek
	game->player.pos_x = (double)game->player_x + 0.5;
	game->player.pos_y = (double)game->player_y + 0.5;
	
	// Player karakterini bul
	player = game->map.map[game->player_y][game->player_x];
	set_player_direction(game, player);
	game->player.move_speed = 0.03;
	game->player.rot_speed = 0.03;
	game->player.key_w = 0;
	game->player.key_s = 0;
	game->player.key_a = 0;
	game->player.key_d = 0;
	game->player.key_left = 0;
	game->player.key_right = 0;
	
	// FPS için başlangıç zamanını ayarlandı
	game->last_frame_time = calc_time();
	debug("init_player: player initialized");
}
