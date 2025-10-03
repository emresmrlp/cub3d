/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:56:24 by ysumeral          #+#    #+#             */
/*   Updated: 2025/10/03 16:59:36 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

static int  check_file(char *path)
{
    char *extension;
    int fd;

    if (!path) // path is NULL?
        return (0);
    extension = ft_strrchr(path, '.'); // (test.cub -> .cub) or (test.txt -> .txt)
    if (!extension || ft_strncmp(extension, ".cub", 5) != 0
        || (path == extension)) // extension is NULL? extension is just ".cub|0" (not test.cubA)? and path is not just ".cub"? controls
    {
        fatal_debug("file extension error");
        return (0);
    }
    fd = open(path, O_RDONLY); //path can open?
    if (fd < 0)
    {
        fatal_debug("file is not exist");
        close(fd);
        return (0);
    }
    close(fd);
    return (1);
}

void parse_map(t_game *game, char *map_path)
{
    (void)game;
    printf("MAX_X: %d, MAX_Y: %d", calc_max(x), calc_max(y));
}

void parse(t_game *game, int argc, char **argv)
{
    int map_path;

    if (argc != 2)
		(fatal_debug("arg error != 2"), fatal_quit(game));
    map_path = argv[1];
    if (check_file(map_path]) == FALSE)
        fatal_quit(game);
    parse_map(game, map_path);
    game->texture.no_path = "./texture/north.xpm"; //NEED PARAM VALUE (ITS JUST TEST)
	game->texture.we_path = "./texture/west.xpm"; //NEED PARAM VALUE (ITS JUST TEST)
	game->texture.so_path = "./texture/south.xpm"; //NEED PARAM VALUE (ITS JUST TEST)
	game->texture.ea_path = "./texture/east.xpm"; //NEED PARAM VALUE (ITS JUST TEST)
    game->texture.ceiling_color[0] = 255; //NEED PARAM VALUE (ITS JUST TEST)
	game->texture.ceiling_color[1] = 255; //NEED PARAM VALUE (ITS JUST TEST)
	game->texture.ceiling_color[2] = 0; //NEED PARAM VALUE (ITS JUST TEST)
	game->texture.floor_color[0] = 128; //NEED PARAM VALUE (ITS JUST TEST)
	game->texture.floor_color[1] = 128; //NEED PARAM VALUE (ITS JUST TEST)
	game->texture.floor_color[2] = 128; //NEED PARAM VALUE (ITS JUST TEST)
}