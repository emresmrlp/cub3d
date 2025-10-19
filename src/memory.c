/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:09:09 by ysumeral          #+#    #+#             */
/*   Updated: 2025/10/19 20:58:09 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/memory.h"

static void cleanup_texture(t_game *game)
{
	if (game->texture.no_wall)
		mlx_destroy_image(game->mlx, game->texture.no_wall);
	if (game->texture.we_wall)
		mlx_destroy_image(game->mlx, game->texture.we_wall);
	if (game->texture.ea_wall)
		mlx_destroy_image(game->mlx, game->texture.ea_wall);
	if (game->texture.so_wall)
		mlx_destroy_image(game->mlx, game->texture.so_wall);
	if (game->texture.background)
		mlx_destroy_image(game->mlx, game->texture.background);
}

static void cleanup_param(t_game *game)
{
	if (game->texture.key)
	{
		free(game->texture.key);
		game->texture.key = NULL;
	}
	if (game->texture.value)
	{
		free(game->texture.value);
		game->texture.value = NULL;
	}
	if (game->texture.no_path)
	{
		free(game->texture.no_path);
		game->texture.no_path = NULL;
	}
	if (game->texture.we_path)
	{
		free(game->texture.we_path);
		game->texture.we_path = NULL;
	}
	if (game->texture.ea_path)
	{
		free(game->texture.ea_path);
		game->texture.ea_path = NULL;
	}
	if (game->texture.so_path)
	{
		free(game->texture.so_path);
		game->texture.so_path = NULL;
	}
}

static void cleanup_map(t_game *game, char ***map)
{
	int	i;

	i = game->map.size_y + 2;
	if (*map)
	{
		while (i--)
		{
			if ((*map)[i])
			{
				free((*map)[i]);
				(*map)[i] = NULL;
			}
		}
		free(*map);
		*map = NULL;
	}
}

void cleanup(t_game *game)
{
	get_next_line(-1);
	if (game)
	{
		cleanup_param(game);
		if (game->map.map_list)
			ft_lstclear(&game->map.map_list, free);
		cleanup_map(game, &game->map.map);
		cleanup_map(game, &game->map.copy);
		if (game->win)
		{
			// YSUMERAL: Destroy the window but do not free the pointer directly because it is managed by the MLX library
			mlx_destroy_window(game->mlx, game->win);
			game->win = NULL;
		}
		if (game->mlx)
		{
			cleanup_texture(game);
			// YSUMERAL: Destroy the display and free the mlx pointer beacause it was allocated by mlx_init() function
			mlx_destroy_display(game->mlx);
			free(game->mlx);
			game->mlx = NULL;
		}
		free(game);
		game = NULL;
	}
}
