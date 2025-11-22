/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:56:24 by ysumeral          #+#    #+#             */
/*   Updated: 2025/11/22 18:15:33 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

static void	check_color(t_game *game, int *i)
{
	int	j;
	int	*color_array;

	if (!ft_strncmp(game->texture.key, "F", 1))
		color_array = game->texture.floor_color;
	else
		color_array = game->texture.ceiling_color;
	j = 0;
	while (j < 3)
	{
		if (color_array[j] < 0 || color_array[j] > 255)
			fatal_quit(game, "Color value must be between 0-255");
		j++;
	}
	while (*(game->texture.value + *i) == ' ' || *(game->texture.value + *i) == '\n')
		(*i)++;
	if (*(game->texture.value + *i) != '\0' && *(game->texture.value + *i) != '\n' && *(game->texture.value + *i) != ' ')
		fatal_quit(game, "Invalid color syntax.");
}

void	parse_color(t_game *game)
{
	int	i;

	i = 0;
	while (*(game->texture.value + i) != '\0' && (*(game->texture.value + i) == ' '
		|| *(game->texture.value + i) == '\n'))
		i++;
	if (*(game->texture.value + i) == '\0')
		fatal_quit(game, "Map value is empty.");
	set_color(game, RED, &i);
	set_color(game, GREEN, &i);
	set_color(game, BLUE, &i);
	check_color(game, &i);
}

void	parse_line(t_game *game, char *line)
{
	int		i;

	i = 0;
	which_line(game, line, &i);
	if (!game->texture.key)
		return ;
	while (line[i] != '\0' && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (game->texture.value)
	{
		free(game->texture.value);
		game->texture.value = NULL;
	}
	game->texture.value = ft_substr(line, i, ft_strlen(line) - i);
	if (!game->texture.value)
	{
		free(game->texture.key);
		game->texture.key = NULL;
		fatal_quit(game, "Value alloc failed.");
	}
	if (!ft_strncmp(game->texture.key, "F", 1) || !ft_strncmp(game->texture.key, "C", 1))
		parse_color(game);
	else
		parse_path(game);
}

static int parse_file(t_game *game, char *map_path, int count)
{
	int		fd;
	char	*line;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		fatal_quit(game, "Map path is not correct.");
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
		fatal_quit(game, "Missing texture or color on the map file");
	return (fd);
}

void parse(t_game *game, int argc, char **argv)
{
	char *map_path;
	int map_fd;
	
	game->texture.key = NULL;
	game->texture.value = NULL;
	game->texture.floor_color[0] = -1;
	game->texture.ceiling_color[0] = -1;
	if (argc != 2)
		fatal_quit(game, "Correct usage: ./cub3D map");
	map_path = argv[1];
	check_file(game, map_path);
	map_fd = parse_file(game, map_path, 0);
	if (!game->texture.no_path || !game->texture.so_path || 
		!game->texture.we_path || !game->texture.ea_path)
		fatal_quit(game, "Missing texture path on the map file.");
	if (game->texture.floor_color[0] == -1)
		fatal_quit(game, "Missing F on the map file.");
	if (game->texture.ceiling_color[0] == -1)
		fatal_quit(game, "Missing C on the map file.");
	parse_map(game, map_fd);
}
