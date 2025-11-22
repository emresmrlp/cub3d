/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:40:34 by ysumeral          #+#    #+#             */
/*   Updated: 2025/11/22 18:15:22 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/memory.h"
#include "../include/game.h"
#include "../include/input.h"
#include "../include/parse.h"
#include "../include/init.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	game = calloc(1, sizeof(t_game));
	if (!game)
		fatal_quit(NULL, "Game struct alloc failed...");
	parse(game, argc, argv);
	init(game);
	register_hooks(game);
	start(game);
	cleanup(game);
	return (0);
}
