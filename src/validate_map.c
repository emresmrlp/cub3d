/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 17:54:02 by ysumeral          #+#    #+#             */
/*   Updated: 2025/11/21 19:31:24 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

static void	print_copy_map_debugger(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map.copy[y] != NULL)
	{
		x = 0;
		while (game->map.copy[y][x] != '\0')
		{
			printf("%c", game->map.copy[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
	printf("\n\n");
}

static int	flood_fill(t_game *game, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->map.size_x + 2
		|| y >= game->map.size_y + 2)
		return (TRUE);
	if (game->map.copy[y][x] == '1' || game->map.copy[y][x] == '.')
		return (TRUE);
	if (game->map.copy[y][x] == '*')
	{
		fatal_debug("flood_fill: space error");
		return (FALSE);
	}
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

static int	copy_create(t_game *game)
{
	int	i;

	i = 0;
	game->map.copy = (char **)ft_calloc(game->map.size_y + 3, sizeof(char *));
	if (!game->map.copy)
	{
		fatal_debug("copy_crate: map copy allocate error");
		return (FALSE);
	}
	while (i < game->map.size_y + 2)
	{
		game->map.copy[i]
			= (char *)ft_calloc(game->map.size_x + 3, sizeof(char));
		if (!game->map.copy[i])
			return (FALSE);
		ft_strlcpy(game->map.copy[i], game->map.map[i],
			game->map.size_x + 3);
		i++;
	}
	debug("copy_create: copy map created");
	return (TRUE);
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

int	validate_map(t_game *game)
{
	set_player_coord(game);
	if (copy_create(game) == FALSE)
		return (FALSE);
	print_copy_map_debugger(game);
	if (flood_fill(game, game->player_x, game->player_y) == FALSE)
		return (FALSE);
	print_copy_map_debugger(game);
	debug("map validate success!!!");
	return (TRUE);
}
