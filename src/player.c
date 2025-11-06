/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkayadib <zkayadib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 05:30:00 by zulfiye           #+#    #+#             */
/*   Updated: 2025/11/16 17:51:35 by zkayadib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/init.h"
#include <math.h>

//dir tek bir konumu ele aldığı için, yalnızca ekranın ortasını görebilirdik
//yelpaze görünümü için plane'e ihtiyaç duyarız
static void set_player_direction_for_WE(t_game *game, char direction)
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
static void set_player_direction(t_game *game, char direction)
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
		set_player_direction_for_WE(game, direction);
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
    game->player.move_speed = 0.1;
    game->player.rot_speed = 0.05;
    debug("init_player: player initialized");
}