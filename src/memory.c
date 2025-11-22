/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:09:09 by ysumeral          #+#    #+#             */
/*   Updated: 2025/11/22 18:12:08 by ysumeral         ###   ########.fr       */
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

static void cleanup_param_value(char **param)
{
	if (*param)
	{
		free(*param);
		*param = NULL;
	}
}

static void cleanup_param(t_game *game)
{
	cleanup_param_value(&game->texture.key);
	cleanup_param_value(&game->texture.value);
	cleanup_param_value(&game->texture.no_path);
	cleanup_param_value(&game->texture.we_path);
	cleanup_param_value(&game->texture.ea_path);
	cleanup_param_value(&game->texture.so_path);
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
			mlx_destroy_window(game->mlx, game->win);
			game->win = NULL;
		}
		if (game->mlx)
		{
			cleanup_texture(game);
			mlx_destroy_display(game->mlx);
			free(game->mlx);
			game->mlx = NULL;
		}
		free(game);
		game = NULL;
	}
}
