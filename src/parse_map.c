/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 17:19:55 by ysumeral          #+#    #+#             */
/*   Updated: 2025/10/18 20:42:59 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

static int check_invalid_char(char *line)
{
    int i;

    i = 0;
    while (line[i] != '\n' && line[i] != '\0')
    {
        if (line[i] != ' ' && line[i] != '1' && line[i] != '0'
            && line[i] != 'N' && line[i] != 'S' && line[i] != 'E'
            && line[i] != 'W')
        {
            free(line);
            fatal_debug("invalid character in map");
            return (FALSE);
        }
        i++;
    }
    return (TRUE);
}

static int check_map(int map_fd)
{
    char *line;
    int is_map;

    is_map = 0;
    line = get_next_line(map_fd);
    while (line != NULL)
    {
        if (is_map == 0 && check_line(line) == TRUE)
            is_map = 1;
        if (is_map == 1)
        {
            printf("%s", line);
            if (check_invalid_char(line) == FALSE)
                return (FALSE);
        }
        free(line);
        line = get_next_line(map_fd);
    }
    free(line);
    return (TRUE);
}

void parse_map(t_game *game, int map_fd)
{
    if (map_fd < 0)
        fatal_debug("map_fd failure"), fatal_quit(game);
    if (check_map(map_fd) == FALSE)
        fatal_debug("check_map failure"), fatal_quit(game);
    close(map_fd);
}