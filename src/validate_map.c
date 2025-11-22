/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 17:54:02 by ysumeral          #+#    #+#             */
/*   Updated: 2025/11/22 20:25:29 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

static int	flood_fill(t_game *game, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->map.size_x + 2
		|| y >= game->map.size_y + 2)
		return (TRUE);
	if (game->map.copy[y][x] == '1' || game->map.copy[y][x] == '.')
		return (TRUE);
	if (game->map.copy[y][x] == '*')
		fatal_quit(game, "Space detected on the map file");
	game->map.copy[y][x] = '.';
	if (flood_fill(game, x + 1, y) == FALSE)
		return (FALSE);
	if (flood_fill(game, x - 1, y) == FALSE)
		return (FALSE);
	if (flood_fill(game, x, y + 1) == FALSE)
		return (FALSE);
	if (flood_fill(game, x, y - 1) == FALSE)
		return (FALSE);
	return (TRUE);
}

static void	copy_create(t_game *game)
{
	int	i;

	i = 0;
	game->map.copy = (char **)ft_calloc(game->map.size_y + 3, sizeof(char *));
	if (!game->map.copy)
		fatal_quit(game, "Copy map alloc failed.");
	while (i < game->map.size_y + 2)
	{
		game->map.copy[i]
			= (char *)ft_calloc(game->map.size_x + 3, sizeof(char));
		if (!game->map.copy[i])
			fatal_quit(game, "Copy map alloc failed.");
		ft_strlcpy(game->map.copy[i], game->map.map[i],
			game->map.size_x + 3);
		i++;
	}
}

static void	set_player_coord(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map.map[y] != NULL)
	{
		x = 0;
		while (game->map.map[y][x] != '\0')
		{
			if (game->map.map[y][x] == 'N' || game->map.map[y][x] == 'W'
				|| game->map.map[y][x] == 'E' || game->map.map[y][x] == 'S')
			{
				game->player_x = x;
				game->player_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

void	validate_map(t_game *game)
{
	set_player_coord(game);
	copy_create(game);
	flood_fill(game, game->player_x, game->player_y);
}
