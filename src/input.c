/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:33:41 by ysumeral          #+#    #+#             */
/*   Updated: 2025/10/02 16:00:30 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/input.h"

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
    debug("keypress detected!");
    printf("key is: %d\n", key);
	if (key == 65307 || key == 113)
        quit(game);
	return(0);
}

void register_hooks(t_game *game)
{
	mlx_hook(game->win, 17, 0, event_click, game);
    mlx_hook(game->win, 2, (1L << 0), event_keypress, game);
}