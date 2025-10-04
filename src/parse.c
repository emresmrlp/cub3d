/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:56:24 by ysumeral          #+#    #+#             */
/*   Updated: 2025/10/04 04:37:57 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

static void parse_color(t_game *game, char *key, char *value)
{
    int i;
    int j;

    i = 0;
    while (*(value + i) != '\0' && (*(value + i) == ' '
        || *(value + i) == '\n'))
        i++;
    if (*(value + i) == '\0')
        (fatal_debug("map value is empty"), fatal_quit(game));
    set_color(game, RED, key, value, &i);
    set_color(game, GREEN, key, value, &i);
    set_color(game, BLUE, key, value, &i);
    j = 0;
    while (j < 3)
    {
        if (game->texture.floor_color[j] < 0 || game->texture.floor_color[j] > 255)
            (fatal_debug("wrong floor rgb color"), fatal_quit(game));
        if (game->texture.ceiling_color[j] < 0 || game->texture.ceiling_color[j] > 255)
            (fatal_debug("wrong ceiling rgb color"), fatal_quit(game));
        j++;
    }
    while (*(value + i) == ' ' || *(value + i) == '\n')
        i++;
    if (*(value + i) != '\0' && *(value + i) != '\n' && *(value + i) != ' ')
        (fatal_debug("invalid syntax in map (color)"), fatal_quit(game));
}

static void parse_path(t_game *game, char *key, char *value)
{
    int i;

    i = 0;
    while (*(value + i) != '\0' && (*(value + i) == ' '
        || *(value + i) == '\n'))
        i++;
    while (*(value + i) != '\0' && (*(value + i) != ' ' && *(value + i) != '\n'))
        i++;
    while (*(value + i) == ' ' || *(value + i) == '\n')
        i++;
    if (*(value + i) != '\0' && *(value + i) != '\n' && *(value + i) != ' ')
        (fatal_debug("invalid syntax in map (color)"), fatal_quit(game));
}

static void parse_line(t_game *game, char *line)
{
    char *key;
    char *value;
    int i;

    i = 0;
    while (*(line + i) != '\0' && *(line + i) == ' ')
        i++;
    if (*(line + i + 1) == ' ')
        key = ft_substr(line, i, 1);
    else if (*(line + i + 1) == ' ')
        key = ft_substr(line, i, 2);
    else
        key = NULL;
    if (!key || (!ft_strncmp(key, "NO", 2) && !ft_strncmp(key, "SO", 2) &&
             !ft_strncmp(key, "WE", 2) && !ft_strncmp(key, "EA", 2) &&
             !ft_strncmp(key, "F", 1) && !ft_strncmp(key, "C", 1)))
        (fatal_debug("invalid key in map"), fatal_quit(game));
    if (ft_strlen(key) == 2)
        value = ft_substr(line, i + 3, ft_strlen(line));
    else
        value = ft_substr(line, i + 2, ft_strlen(line));
    if (!ft_strncmp(key, "F", 1) || !ft_strncmp(key, "C", 1))
        parse_color(game, key, value);
    else
        parse_path(game, key, value);
}

static void parse_file(t_game *game, char *map_path)
{
	int		fd;
	char	*line;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		(fatal_quit(game), fatal_debug("map_path error"));
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (check_line(line) == TRUE)
            parse_line(game, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (counter);
}

void parse(t_game *game, int argc, char **argv)
{
    char *map_path;

    if (argc != 2)
		(fatal_debug("arg error != 2"), fatal_quit(game));
    map_path = argv[1];
    if (check_file(map_path) == FALSE)
        fatal_quit(game);
    parse_file(game, map_path);
    game->texture.no_path = "./texture/north.xpm"; //NEED PARAM VALUE (ITS JUST TEST)
	game->texture.we_path = "./texture/west.xpm"; //NEED PARAM VALUE (ITS JUST TEST)
	game->texture.so_path = "./texture/south.xpm"; //NEED PARAM VALUE (ITS JUST TEST)
	game->texture.ea_path = "./texture/east.xpm"; //NEED PARAM VALUE (ITS JUST TEST)
}