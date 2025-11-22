/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_and_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zulfiye <zulfiye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 15:21:00 by zulfiye           #+#    #+#             */
/*   Updated: 2025/11/22 15:31:25 by zulfiye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/input.h"
#include "../include/raycast.h"
#include "../include/init.h"
#include <sys/time.h>


//yeni_x = (eski_x * cos(a)) - (eski_y * sin(a))
//yeni_y = (eski_x * sin(a)) + (eski_y * cos(a))
//hem dir için hem de plane için uygulamama sebebimiz, başta kurduğumuz açının bozulmaması için
void rotate_left(t_game *game)
{
	double old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(-game->player.rot_speed) - 
						 game->player.dir_y * sin(-game->player.rot_speed);
	game->player.dir_y = old_dir_x * sin(-game->player.rot_speed) + 
						 game->player.dir_y * cos(-game->player.rot_speed);
	
	double old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(-game->player.rot_speed) - 
						   game->player.plane_y * sin(-game->player.rot_speed);
	game->player.plane_y = old_plane_x * sin(-game->player.rot_speed) + 
						   game->player.plane_y * cos(-game->player.rot_speed);
}

void rotate_right(t_game *game)
{
	double old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(game->player.rot_speed) - 
						 game->player.dir_y * sin(game->player.rot_speed);
	game->player.dir_y = old_dir_x * sin(game->player.rot_speed) + 
						 game->player.dir_y * cos(game->player.rot_speed);
	
	double old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(game->player.rot_speed) - 
						   game->player.plane_y * sin(game->player.rot_speed);
	game->player.plane_y = old_plane_x * sin(game->player.rot_speed) + 
						   game->player.plane_y * cos(game->player.rot_speed);
}
long calc_time(void)
{
	long milliseconds;
	struct timeval time;
	gettimeofday(&time, NULL);
	milliseconds = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (milliseconds);
}

int event_click(void *param)
{
	t_game * game;
	
	game = (t_game *)param;
	quit(game);
	return(0);
}