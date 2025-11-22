/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:33:41 by ysumeral          #+#    #+#             */
/*   Updated: 2025/11/22 21:02:34 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/input.h"
#include "../include/raycast.h"
#include <sys/time.h>

static int	event_keypress(int key, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (key == 65307 || key == 113)
		quit(game, "Goodbye!");
	else if (key == 119)
		game->player.key_w = 1;
	else if (key == 115)
		game->player.key_s = 1;
	else if (key == 100)
		game->player.key_d = 1;
	else if (key == 97)
		game->player.key_a = 1;
	else if (key == 65361)
		game->player.key_left = 1;
	else if (key == 65363)
		game->player.key_right = 1;
	return (0);
}

static int	event_keyrelease(int key, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (key == 119)
		game->player.key_w = 0;
	else if (key == 115)
		game->player.key_s = 0;
	else if (key == 100)
		game->player.key_d = 0;
	else if (key == 97)
		game->player.key_a = 0;
	else if (key == 65361)
		game->player.key_left = 0;
	else if (key == 65363)
		game->player.key_right = 0;
	return (0);
}

static void	apply_events(t_game *game)
{
	if (game->player.key_w)
		move_forward(game);
	if (game->player.key_s)
		move_backward(game);
	if (game->player.key_a)
		move_left(game);
	if (game->player.key_d)
		move_right(game);
	if (game->player.key_left)
		rotate_left(game);
	if (game->player.key_right)
		rotate_right(game);
}

static int	render_loop(void *param)
{
	t_game	*game;
	long	current_time;
	long	time_control;

	game = (t_game *)param;
	current_time = calc_time();
	time_control = current_time - game->last_frame_time;
	if (time_control < FRAME_TIME_MS)
		return (0);
	game->last_frame_time = current_time;
	apply_events(game);
	raycast(game);
	mlx_put_image_to_window(game->mlx, game->win,
		game->texture.background, 0, 0);
	return (0);
}

void	register_hooks(t_game *game)
{
	mlx_hook(game->win, 17, 0, event_click, game);
	mlx_hook(game->win, 2, (1L << 0), event_keypress, game);
	mlx_hook(game->win, 3, (1L << 1), event_keyrelease, game);
	mlx_loop_hook(game->mlx, render_loop, game);
}
