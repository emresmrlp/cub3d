/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 16:46:48 by ysumeral          #+#    #+#             */
/*   Updated: 2025/11/22 18:17:25 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include "game.h"
# include <math.h>

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	first_dist_x;
	double	first_dist_y;
	double	routine_dist_x;
	double	routine_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	wall_x;
	int		tex_x;
}	t_ray;

typedef struct s_draw
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	char	*tex_data;
	int		tex_line;
	int		tex_bpp;
}	t_draw;

void	raycast(t_game *game);
void	init_ray(t_game *game, t_ray *ray, int x);
void	dda(t_game *game, t_ray *ray);
void	calculate_wall_distance(t_ray *ray);
void	draw_vertical_line(t_game *game, t_ray *ray, int x);

void	*get_texture(t_game *game, t_ray *ray);
void	calculate_tex_x(t_game *game, t_ray *ray);
int		calculate_tex_y(int y, int line_height, int img_height);

#endif