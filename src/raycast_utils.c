/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 15:15:24 by zulfiye           #+#    #+#             */
/*   Updated: 2025/11/22 21:25:19 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/raycast.h"

int	calculate_tex_y(int y, int line_height, int img_height)
{
	int	tex_y;

	tex_y = (int)((y - SIZE_Y / 2 + line_height / 2)
			* img_height / line_height);
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= img_height)
		tex_y = img_height - 1;
	return (tex_y);
}

void	calculate_tex_x(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_x = game->player.pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = game->player.pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * (double)game->texture.img_width);
	if (ray->side == 0 && ray->ray_dir_x < 0)
		ray->tex_x = game->texture.img_width - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y > 0)
		ray->tex_x = game->texture.img_width - ray->tex_x - 1;
}

void	*get_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (game->texture.ea_wall);
		else
			return (game->texture.we_wall);
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return (game->texture.so_wall);
		else
			return (game->texture.no_wall);
	}
}
