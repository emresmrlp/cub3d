/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:43:54 by ysumeral          #+#    #+#             */
/*   Updated: 2025/10/02 21:08:24 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/draw.h"

static int rgb_to_hex(int r, int g, int b)
{
    int hex;

    hex = (r << 16) | (g << 8) | b;
    return (hex);
}

static void draw_pixel(t_game *game, int x, int y, int color)
{
    char *pixel;

    pixel = game->texture.addr + (y * game->texture.x_byte + x * 4);
    *(unsigned int *)pixel = color;
}

void draw_background(t_game *game)
{
    int floor_color;
    int ceiling_color;

    debug("draw starting...");
    floor_color = rgb_to_hex(game->texture.floor_color[0], game->texture.floor_color[1],
        game->texture.floor_color[2]);
    ceiling_color = rgb_to_hex(game->texture.ceiling_color[0], game->texture.ceiling_color[1],
        game->texture.ceiling_color[2]);
    debug("draw colors setted.");
    while (game->texture.x < SIZE_X)
    {
        game->texture.y = 0;
        while (game->texture.y < SIZE_Y)
        {
            if(game->texture.y > SIZE_Y / 2)
                draw_pixel(game, game->texture.x, game->texture.y, floor_color);
            else
                draw_pixel(game, game->texture.x, game->texture.y, ceiling_color);
            game->texture.y++;
        }
        game->texture.x++;
    }
    mlx_put_image_to_window(game->mlx, game->win, game->texture.background, 0, 0);
}
