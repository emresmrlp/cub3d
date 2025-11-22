/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 07:52:03 by zulfiye           #+#    #+#             */
/*   Updated: 2025/11/22 21:26:37 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/raycast.h"

void	init_ray(t_game *game, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)SIZE_X - 1;
	ray->ray_dir_x = game->player.dir_x + game->player.plane_x * ray->camera_x;
	ray->ray_dir_y = game->player.dir_y + game->player.plane_y * ray->camera_x;
	ray->map_x = (int)game->player.pos_x;
	ray->map_y = (int)game->player.pos_y;
	if (ray->ray_dir_x == 0)
		ray->routine_dist_x = INFINITY;
	else
		ray->routine_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->routine_dist_y = INFINITY;
	else
		ray->routine_dist_y = fabs(1 / ray->ray_dir_y);
}

static void	init_first_dist(t_game *game, t_ray *ray)
{
	ray->hit = 0;
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->first_dist_x = (game->player.pos_x - ray->map_x)
			* ray->routine_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->first_dist_x = (ray->map_x + 1.0 - game->player.pos_x)
			* ray->routine_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->first_dist_y = (game->player.pos_y - ray->map_y)
			* ray->routine_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->first_dist_y = (ray->map_y + 1.0 - game->player.pos_y)
			* ray->routine_dist_y;
	}
}

void	dda(t_game *game, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->first_dist_x < ray->first_dist_y)
		{
			ray->first_dist_x += ray->routine_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->first_dist_y += ray->routine_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (game->map.map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

void	calculate_wall_distance(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->first_dist_x - ray->routine_dist_x);
	else
		ray->perp_wall_dist = (ray->first_dist_y - ray->routine_dist_y);
}

void	raycast(t_game *game)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < SIZE_X)
	{
		init_ray(game, &ray, x);
		init_first_dist(game, &ray);
		dda(game, &ray);
		calculate_wall_distance(&ray);
		draw_vertical_line(game, &ray, x);
		x++;
	}
}
