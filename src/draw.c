/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:43:54 by ysumeral          #+#    #+#             */
/*   Updated: 2025/10/02 16:02:46 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/draw.h"
#include "../include/game.h"

static int rgb_to_hex(int r, int g, int b)
{
    int hex;

    hex = (r << 16) | (g << 8) | b;
    return (hex);
}

void draw_background(t_game *game)
{
    (void)rgb_to_hex(0, 0, 0);
    (void)game;
}