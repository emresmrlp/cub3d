/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 03:40:25 by ysumeral          #+#    #+#             */
/*   Updated: 2025/10/04 04:20:38 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

int  check_file(char *path)
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

int check_line(char *line)
{
    int i;

    if (ft_strncmp(line, "\n", 1) || ft_strncmp(line, " \n", 2))
        return (FALSE);
    i = 0;
    while (*(line + i) != '\0' && (*(line + i) == ' ' || *(line + i) == '\n'))
        i++;
    if (*(line + i) == '\0')
        return (FALSE);
    return (TRUE);
}

void set_color(t_game *game, int color, char *key, char *value, int *loc)
{
    int rgb;

    rgb = ft_atoi(value + *loc);
    while (*(value + *loc) != '\0' && ft_isdigit(*(value + *loc)))
        i++;
    if (*(value + *loc) != ',')
        (fatal_quit(game), fatal_debug("map file is incorrect (in colors)"));
    if (key == 'F')
        game->texture.floor_color[color] = rgb;
    if (key == 'C')
        game->texture.ceiling_color[color] = rgb;
}