/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:56:24 by ysumeral          #+#    #+#             */
/*   Updated: 2025/10/03 14:13:12 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

static int  check_extension(char *path)
{
    char *extension;

    if (!path)
        return (0);
    extension = ft_strrchr(path, '.');
    printf("%s\n", extension);
    if (!extension || ft_strncmp(extension, ".cub", 5) != 0
        || (path == extension))
        return (0);
    return (1);
}

void parse(t_game *game, int argc, char **argv)
{
    if (argc != 2)
		(fatal_debug("arg error != 2"), fatal_quit(game));
    if (check_extension(argv[1]) == FALSE)
    {
        (fatal_debug("file extension error"), fatal_quit(game));
    }
    game->texture.ceiling_color[0] = 255; //NEED PARAM VALUE (ITS JUST TEST)
	game->texture.ceiling_color[1] = 255; //NEED PARAM VALUE (ITS JUST TEST)
	game->texture.ceiling_color[2] = 0; //NEED PARAM VALUE (ITS JUST TEST)
	game->texture.floor_color[0] = 128; //NEED PARAM VALUE (ITS JUST TEST)
	game->texture.floor_color[1] = 128; //NEED PARAM VALUE (ITS JUST TEST)
	game->texture.floor_color[2] = 128; //NEED PARAM VALUE (ITS JUST TEST)
}