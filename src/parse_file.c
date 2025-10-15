/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkayadib <zkayadib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:56:24 by ysumeral          #+#    #+#             */
/*   Updated: 2025/10/15 19:10:22 by zkayadib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

static void	check_color(t_game *game, char *key, char *value, int *i)
{
	int	j;
	int	*color_array;

	if (!ft_strncmp(key, "F", 1))
		color_array = game->texture.floor_color;
	else
		color_array = game->texture.ceiling_color;
	j = 0;
	while (j < 3)
	{
		if (color_array[j] < 0 || color_array[j] > 255)
			(fatal_debug("wrong rgb color (must be 0-255)"), fatal_quit(game));
		j++;
	}
	while (*(value + *i) == ' ' || *(value + *i) == '\n')
		(*i)++;
	if (*(value + *i) != '\0' && *(value + *i) != '\n' && *(value + *i) != ' ')
		(fatal_debug("invalid syntax in map (color)"), fatal_quit(game));
}

void	parse_color(t_game *game, char *key, char *value)
{
	int	i;

	i = 0;
	while (*(value + i) != '\0' && (*(value + i) == ' '
		|| *(value + i) == '\n'))
		i++;
	if (*(value + i) == '\0')
		(fatal_debug("map value is empty"), fatal_quit(game));
	set_color(game, RED, key, value, &i);
	set_color(game, GREEN, key, value, &i);
	set_color(game, BLUE, key, value, &i);
	check_color(game, key, value, &i);
}

void	parse_line(t_game *game, char *line)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	key = which_line(game, line, &i);
	if (!key)
		return ;
	while (line[i] != '\0' && (line[i] == ' ' || line[i] == '\t'))
		i++;
	value = ft_substr(line, i, ft_strlen(line) - i);
	if (!value)
	{
		free(key);
		(fatal_debug("malloc error on value"), fatal_quit(game));
	}
	if (!ft_strncmp(key, "F", 1) || !ft_strncmp(key, "C", 1))
		parse_color(game, key, value);
	else
		parse_path(game, key, value);
	free(key);
	free(value);
}


static int parse_file(t_game *game, char *map_path, int count)
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
		{
			parse_line(game, line);
			count++;
			if (count == 6)
			{
				free(line);
				break;
			}
		}
		free(line);
		line = get_next_line(fd);
	}
	if (count < 6)
		(fatal_debug("missing texture or color in map file"), fatal_quit(game));
	return (fd);
}

void parse(t_game *game, int argc, char **argv)
{
    char *map_path;
    int map_fd;
	
    if (argc != 2)
		(fatal_debug("arg error != 2"), fatal_quit(game));
    map_path = argv[1];
    if (check_file(map_path) == FALSE)
        fatal_quit(game);
    map_fd = parse_file(game, map_path, 0);
    if (!game->texture.no_path || !game->texture.so_path || 
        !game->texture.we_path || !game->texture.ea_path)
        (fatal_debug("missing texture path in map file"), fatal_quit(game));
    if (game->texture.floor_color[0] == -1)
        (fatal_debug("missing F (floor color) in map file"), fatal_quit(game));
    if (game->texture.ceiling_color[0] == -1)
        (fatal_debug("missing C (ceiling color) in map file"), fatal_quit(game));
    
	// for find first line --> game->map.first_line
	// for other line --> get_next_line(map_fd)
    find_map(game, map_fd);
    printf("first line of man:%s", game->map.first_line);
	char *line = get_next_line(map_fd);
	printf("second line of map:%s", line);
	// you should close map_fd when your work finish with map
    // close(map_fd);you should close map_fd when your work finish with map
}