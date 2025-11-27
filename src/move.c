/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 04:10:35 by zkayadib          #+#    #+#             */
/*   Updated: 2025/11/27 20:24:06 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/raycast.h"

void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + game->player.dir_x
		* game->player.move_speed;
	new_y = game->player.pos_y + game->player.dir_y
		* game->player.move_speed;
	if (ctrl(game, (int)new_x, (int)new_y))
	{
		game->player.pos_x = new_x;
		game->player.pos_y = new_y;
	}
}

void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x - game->player.dir_x
		* game->player.move_speed;
	new_y = game->player.pos_y - game->player.dir_y
		* game->player.move_speed;
	if (ctrl(game, (int)new_x, (int)new_y))
	{
		game->player.pos_x = new_x;
		game->player.pos_y = new_y;
	}
}

void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x - game->player.plane_x
		* game->player.move_speed;
	new_y = game->player.pos_y - game->player.plane_y
		* game->player.move_speed;
	if (ctrl(game, (int)new_x, (int)new_y))
	{
		game->player.pos_x = new_x;
		game->player.pos_y = new_y;
	}
}

void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + game->player.plane_x
		* game->player.move_speed;
	new_y = game->player.pos_y + game->player.plane_y
		* game->player.move_speed;
	if (ctrl(game, (int)new_x, (int)new_y))
	{
		game->player.pos_x = new_x;
		game->player.pos_y = new_y;
	}
}
