/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zulfiye <zulfiye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:33:41 by ysumeral          #+#    #+#             */
/*   Updated: 2025/11/22 03:55:31 by zulfiye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/input.h"
#include "../include/raycast.h"
#include <sys/time.h>

//Yeni konum = Eski konum + (Yön vektörü × hız)
static void move_forward(t_game *game)
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
static void move_backward(t_game *game)
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
static void move_left(t_game *game)
{
	double new_x = game->player.pos_x - game->player.plane_x * game->player.move_speed;
	double new_y = game->player.pos_y - game->player.plane_y * game->player.move_speed;
	
	if (game->map.map[(int)new_y][(int)new_x] != '1')
	{
		game->player.pos_x = new_x;
		game->player.pos_y = new_y;
	}
}

static void move_right(t_game *game)
{
	double new_x = game->player.pos_x + game->player.plane_x * game->player.move_speed;
	double new_y = game->player.pos_y + game->player.plane_y * game->player.move_speed;
	
	if (game->map.map[(int)new_y][(int)new_x] != '1')
	{
		game->player.pos_x = new_x;
		game->player.pos_y = new_y;
	}
}

//yeni_x = (eski_x * cos(a)) - (eski_y * sin(a))
//yeni_y = (eski_x * sin(a)) + (eski_y * cos(a))
//hem dir için hem de plane için uygulamama sebebimiz, başta kurduğumuz açının bozulmaması için
static void rotate_left(t_game *game)
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

static void rotate_right(t_game *game)
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

static int event_click(void *param)
{
	t_game * game;
	
	game = (t_game *)param;
	quit(game);
	return(0);
}

static int event_keypress(int key, void *param)
{
	t_game * game;
	
	game = (t_game *)param;
	// debug("keypress detected!");
	// printf("key is: %d\n", key);
	if (key == 65307 || key == 113)
		quit(game);
	else if (key == 119) //W
        game->player.key_w = 1;
	else if (key == 115) //S
        game->player.key_s = 1;
	else if (key == 100) //D
        game->player.key_d = 1;
	else if (key == 97) //A
        game->player.key_a = 1;
	else if (key == 65361)
        game->player.key_left = 1;
	else if (key == 65363)
        game->player.key_right = 1;
	return (0);
}

static int event_keyrelease(int key, void *param)
{
	t_game * game;
	
	game = (t_game *)param;
	if (key == 119) //W
        game->player.key_w = 0;
	else if (key == 115) //S
        game->player.key_s = 0;
	else if (key == 100) //D
        game->player.key_d = 0;
	else if (key == 97) //A
        game->player.key_a = 0;
	else if (key == 65361)
        game->player.key_left = 0;
	else if (key == 65363)
        game->player.key_right = 0;
	return (0);
}

long calc_time(void)
{
	long milliseconds;
	struct timeval time;
	gettimeofday(&time, NULL);
	milliseconds = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (milliseconds);
}

static void apply_events(t_game *game)
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

static int render_loop(void *param)
{
	t_game *game = (t_game *)param;
	long current_time;
	long time_control;
	
	current_time = calc_time();
	time_control = current_time - game->last_frame_time;
	
	// FPS sınırlama: hedef frame time'dan az süre geçtiyse render'ı atla
	if (time_control < FRAME_TIME_MS)
		return (0);
	game->last_frame_time = current_time;
	apply_events(game);
	raycast(game);
	mlx_put_image_to_window(game->mlx, game->win, game->texture.background, 0, 0);
	
	return (0);
}

void register_hooks(t_game *game)
{
	mlx_hook(game->win, 17, 0, event_click, game);
	mlx_hook(game->win, 2, (1L << 0), event_keypress, game);
    mlx_hook(game->win, 3, (1L << 1), event_keyrelease, game);
	mlx_loop_hook(game->mlx, render_loop, game);
}
