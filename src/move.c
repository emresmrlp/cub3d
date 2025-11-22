/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zulfiye <zulfiye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 04:10:35 by zulfiye           #+#    #+#             */
/*   Updated: 2025/11/22 04:12:24 by zulfiye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/input.h"
#include "../include/raycast.h"
#include <sys/time.h>

//Yeni konum = Eski konum + (Yön vektörü × hız)
void move_forward(t_game *game)
{
	double new_x = game->player.pos_x + game->player.dir_x * game->player.move_speed;
	double new_y = game->player.pos_y + game->player.dir_y * game->player.move_speed;
	
	//duvar kontrolü
	if (game->map.map[(int)new_y][(int)new_x] != '1')
	{
		game->player.pos_x = new_x;
		game->player.pos_y = new_y;
	}
}

//Yeni konum = Eski konum - (Yön vektörü × hız)
void move_backward(t_game *game)
{
	double new_x = game->player.pos_x - game->player.dir_x * game->player.move_speed;
	double new_y = game->player.pos_y - game->player.dir_y * game->player.move_speed;
	
	if (game->map.map[(int)new_y][(int)new_x] != '1')
	{
		game->player.pos_x = new_x;
		game->player.pos_y = new_y;
	}
}

//plane, oyuncunun görüş açısının genişliğini temsil eder
//formul aynı, ancak vektör değişiyor(plane)
void move_left(t_game *game)
{
	double new_x = game->player.pos_x - game->player.plane_x * game->player.move_speed;
	double new_y = game->player.pos_y - game->player.plane_y * game->player.move_speed;
	
	if (game->map.map[(int)new_y][(int)new_x] != '1')
	{
		game->player.pos_x = new_x;
		game->player.pos_y = new_y;
	}
}

void move_right(t_game *game)
{
	double new_x = game->player.pos_x + game->player.plane_x * game->player.move_speed;
	double new_y = game->player.pos_y + game->player.plane_y * game->player.move_speed;
	
	if (game->map.map[(int)new_y][(int)new_x] != '1')
	{
		game->player.pos_x = new_x;
		game->player.pos_y = new_y;
	}
}