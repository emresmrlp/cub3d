/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkayadib <zkayadib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:43:50 by ysumeral          #+#    #+#             */
/*   Updated: 2025/11/17 18:05:17 by zkayadib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include <stdio.h>
# include <stdlib.h>
# include "../external/libft/libft.h"
# include "../external/gnl/get_next_line.h"
# include "../external/mlx/mlx.h"
# define SIZE_X 1024
# define SIZE_Y 512
# define TRUE 1
# define FALSE 0

typedef struct s_texture
{
	char *key;
	char *value;
	int ceiling_color[3];
	int floor_color[3];
	int x;
	int y;
	int img_height;
	int img_width;
	void *no_wall;
	char *no_path;
	void *so_wall;
	char *so_path;
	void *we_wall;
	char *we_path;
	void *ea_wall;
	char *ea_path;
	void *background;
	char *addr;
	int bits_pixel;
	int x_byte;
	int endian;
}	t_texture;

typedef struct s_map
{
	t_list	*map_list;
	char	**map;
	char	**copy;
	int		size_x;
	int		size_y;
}	t_map;

typedef struct s_player
{
    double  pos_x;      // Oyuncunun x pozisyonu
    double  pos_y;      // Oyuncunun y pozisyonu
    double  dir_x;      // Bakış yönü vektörü x
    double  dir_y;      // Bakış yönü vektörü y
    double  plane_x;    // Kamera düzlemi vektörü x
    double  plane_y;    // Kamera düzlemi vektörü y
    double  move_speed; // Hareket hızı
    double  rot_speed;  // Dönüş hızı
}   t_player;

typedef struct s_game 
{
	void		*mlx;
	void		*win;
	int			player_x;
	int			player_y;
	t_texture	texture;
	t_map		map;
	t_player    player;
}	t_game;

void	start(t_game *game);
void	quit(t_game *game);
void	fatal_quit(t_game *game);

#endif

//add: s_player struct'ı
//add: s_game struct'ına t_player değeri eklendi