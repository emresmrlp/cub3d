/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:33:41 by ysumeral          #+#    #+#             */
/*   Updated: 2025/11/21 16:49:35 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/input.h"
#include "../include/raycast.h"

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
		move_forward(game);
	else if (key == 115) //S
		move_backward(game);
	else if (key == 100) //D
		move_right(game);
	else if (key == 97) //A
		move_left(game);
	else if (key == 65361)
		rotate_left(game);
	else if (key == 65363)
		rotate_right(game);
	
	return (0);
}

static int render_loop(void *param)
{
	t_game *game = (t_game *)param;
	
	raycast(game);
	mlx_put_image_to_window(game->mlx, game->win, game->texture.background, 0, 0);
	
	return (0);
}

void register_hooks(t_game *game)
{
	mlx_hook(game->win, 17, 0, event_click, game);
	mlx_hook(game->win, 2, (1L << 0), event_keypress, game);
	mlx_loop_hook(game->mlx, render_loop, game);
}
