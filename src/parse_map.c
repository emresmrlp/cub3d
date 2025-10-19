/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 17:19:55 by ysumeral          #+#    #+#             */
/*   Updated: 2025/10/19 21:27:38 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

static int check_invalid_char(t_game *game, char *line)
{
    int i;

    i = 0;
    while (line[i] != '\n' && line[i] != '\0')
    {
        if (line[i] != ' ' && line[i] != '1' && line[i] != '0'
            && line[i] != 'N' && line[i] != 'S' && line[i] != 'E'
            && line[i] != 'W')
        {
            fatal_debug("invalid character in map");
            return (FALSE);
        }
        else if (line[i] == 'N' || line[i] == 'S'
            || line[i] == 'E' || line[i] == 'W')
        {
            if (game->player_x != -1 && game->player_y != -1)
            {
                fatal_debug("multiple player in map");
                return (FALSE);
            }
            game->player_x = 0;
            game->player_y = 0;
        }
        i++;
    }
    return (TRUE);
}

static int read_map_to_list(t_game *game, int map_fd)
{
    t_list *new_node;
    char *line;
    int is_map;

    is_map = 0;
    game->map.map_list = NULL;
    line = get_next_line(map_fd);
    while (line != NULL)
    {
        if (is_map == 0 && check_line(line) == TRUE)
            is_map = 1;
        if (is_map == 1)
        {
            //printf("LINE: %s", line);
            new_node = ft_lstnew(line);
            if (!new_node)
            {
                fatal_debug("node error");
                free(line);
                return (FALSE);
            } 
            ft_lstadd_back(&game->map.map_list, new_node);
            if (check_invalid_char(game, line) == FALSE)
                return (FALSE);
        }
        if (is_map == 0)
            free(line);
        line = get_next_line(map_fd);
    }
    if (game->player_x == -1 || game->player_y == -1)
    {
        fatal_debug("no player in map!");
        return (FALSE);
    }
    if (is_map == 0 || game->map.map_list == NULL)
    {
        fatal_debug("read_map_to_list: map is empty?");
        return (FALSE);
    }
    free(line);
    return (TRUE);
}

static void calc_max_dimension(void *content, void *param, int *index)
{
    char *line;
    int len;
    t_game *game;

    (void)index;
    line = (char *)content;
    game = (t_game *)param;
    game->map.size_y++;
	len = 0;
	while (line[len] != '\0')
		len++;
	if (*(line + len - 1) == '\n')
		len = len - 1;
	if (game->map.size_x == 0)
		game->map.size_x = len;
	else if (game->map.size_x < len)
		game->map.size_x = len;
}

static void alloc_map(void *content, void *param, int *index)
{
    char    *line;
    t_game  *game;
    int     i;
    int     i_line;
    int     new_size;

    i = 0;
    i_line = 0;
    line = (char *)content;
    game = (t_game *)param;
    new_size = game->map.size_x + 2;
    game->map.map[*index] = (char *)ft_calloc(new_size + 3, sizeof(char));
    if (!game->map.map[*index])
        fatal_debug("map allocation error"), fatal_quit(game);
    if (*index == 0 || *index == game->map.size_y + 1)
    {
        while (i < new_size)
        {
            game->map.map[*index][i] = '*';
            i++;
        }
    }
    else
    {
        game->map.map[*index][i] = '*';
        i++;
        while (i < new_size && line[i_line] != '\0' && line[i_line] != '\n')
        {
            if (line[i_line] == ' ')
                game->map.map[*index][i] = '*'; //padding
            else
                game->map.map[*index][i] = line[i_line];
            i++;
            i_line++;
        }
        game->map.map[*index][i] = '*';
        while (i < new_size)
        {
            game->map.map[*index][i] = '*'; //padding
            i++;
        }
    }
    printf("DEBUG: line %d allocated\n", *index + 1);
    *index = *index + 1;
}

static void print_map_debugger(t_game *game)
{
    int x;
    int y;

    y = 0;
    while(game->map.map[y] != NULL)
    {
        x = 0;
        while(game->map.map[y][x] != '\0')
        {
            printf("%c", game->map.map[y][x]);
            x++;
        }
        printf("\n");
        y++;
    }
}

void parse_map(t_game *game, int map_fd)
{
    int y;
    t_list *top_node;
    t_list *bottom_node;
    
    y = 0;
    if (map_fd < 0)
        fatal_debug("map_fd failure"), fatal_quit(game);
    game->player_x = -1;
    game->player_y = -1;
    if (read_map_to_list(game, map_fd) == FALSE)
        fatal_debug("read_map_to_list failure"), fatal_quit(game);
    printf("PLAYER COORD: X: %d and Y: %d\n", game->player_x, game->player_y);
    game->map.size_x = 0;
    game->map.size_y = 0;
    ft_lstiter(game->map.map_list, calc_max_dimension, (void *)game, 0);
    debug("parse_map: calc dimension success");
    printf("MAP SIZE X IS: %d\n", game->map.size_x);
    printf("MAP SIZE Y IS: %d\n", game->map.size_y);
    game->map.map = (char **)ft_calloc(game->map.size_y + 3, sizeof(char *));
    if (!game->map.map)
        fatal_debug("map allocation error"), fatal_quit(game);
    top_node = ft_lstnew(NULL);
    bottom_node = ft_lstnew(NULL);
    ft_lstadd_front(&game->map.map_list, top_node);
    ft_lstadd_back(&game->map.map_list, bottom_node);
    ft_lstiter(game->map.map_list, alloc_map, (void *)game, &y);
    debug("map allocated success");
    print_map_debugger(game);
    if (validate_map(game) == FALSE)
        fatal_debug("map can not validate"), fatal_quit(game);
    printf("PLAYER COORD: X: %d and Y: %d\n", game->player_x, game->player_y);
    close(map_fd);
}
