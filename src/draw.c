/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zulfiye <zulfiye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 15:13:57 by zulfiye           #+#    #+#             */
/*   Updated: 2025/11/22 15:17:04 by zulfiye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/raycast.h"

static void draw_ceiling(t_game *game, int x, int draw_start)
{
    int y;
    int ceiling_color;
    char *pixel;
    
    ceiling_color = (game->texture.ceiling_color[0] << 16) | 
                    (game->texture.ceiling_color[1] << 8) | 
                    game->texture.ceiling_color[2];
    y = 0;
    while (y < draw_start)
    {
        pixel = game->texture.addr + (y * game->texture.x_byte + x * 4);
        *(unsigned int *)pixel = ceiling_color;
        y++;
    }
}

static void draw_floor(t_game *game, int x, int draw_end)
{
    int y;
    int floor_color;
    char *pixel;
    
    floor_color = (game->texture.floor_color[0] << 16) | 
                  (game->texture.floor_color[1] << 8) | 
                  game->texture.floor_color[2];
    y = draw_end + 1;
    while (y < SIZE_Y)
    {
        pixel = game->texture.addr + (y * game->texture.x_byte + x * 4);
        *(unsigned int *)pixel = floor_color;
        y++;
    }
}

static void draw_wall_line(t_game *game, t_ray *ray, t_draw *draw, int x)
{
    int y;
    int tex_y;
    int color;
    char *pixel;
    
    y = draw->draw_start;
    while (y <= draw->draw_end)
    {
        tex_y = calculate_tex_y(y, draw->line_height, game->texture.img_height);
        color = *(int *)(draw->tex_data + (tex_y * draw->tex_line + ray->tex_x * (draw->tex_bpp / 8)));
        pixel = game->texture.addr + (y * game->texture.x_byte + x * 4);
        *(unsigned int *)pixel = color;
        y++;
    }
}

static void init_draw_data(t_draw *draw, void *texture, t_ray *ray)
{
    int tex_endian;
    
    draw->tex_data = mlx_get_data_addr(texture, &draw->tex_bpp, 
                                       &draw->tex_line, &tex_endian);
    draw->line_height = (int)(SIZE_Y / ray->perp_wall_dist);
    draw->draw_start = -draw->line_height / 2 + SIZE_Y / 2;
    if (draw->draw_start < 0)
        draw->draw_start = 0;
    draw->draw_end = draw->line_height / 2 + SIZE_Y / 2;
    if (draw->draw_end >= SIZE_Y)
        draw->draw_end = SIZE_Y - 1;
}

void draw_vertical_line(t_game *game, t_ray *ray, int x)
{
    void    *texture;
    t_draw  draw;
    
    texture = get_texture(game, ray);
    if (!texture)
        return;
    init_draw_data(&draw, texture, ray);
    if (!draw.tex_data)
        return;
    calculate_tex_x(game, ray);
    draw_ceiling(game, x, draw.draw_start);
    draw_wall_line(game, ray, &draw, x);
    draw_floor(game, x, draw.draw_end);
}