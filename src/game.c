/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:10:47 by ysumeral          #+#    #+#             */
/*   Updated: 2025/11/22 17:56:39 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game.h"
#include "../include/memory.h"

void	start(t_game *game)
{
	mlx_loop(game->mlx);
}

void	quit(t_game *game, char *message)
{
	if (message != NULL)
		printf("%s", message);
	cleanup(game);
	exit(0);
}

void	fatal_quit(t_game *game, char *message)
{
	if (message != NULL)
	{
		printf("Error\n");
		printf("%s", message);
	}
	cleanup(game);
	exit(1);
}
