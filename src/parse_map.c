/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 17:19:55 by ysumeral          #+#    #+#             */
/*   Updated: 2025/11/28 15:46:19 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

static void	map_to_lst(t_game *game, int map_fd, char *line)
{
	t_list	*new_node;
	int		x;

	x = 0;
	new_node = ft_lstnew(line);
	if (!new_node)
	{
		close(map_fd);
		fatal_quit(game, "Map reading failed.");
	}
	ft_lstadd_back(&game->map.map_list, new_node);
	check_invalid_char(game, map_fd, line);
	while (line[x] == ' ')
		x++;
	if (line[x] == '\0' || line[x] == '\n')
	{
		close(map_fd);
		fatal_quit(game, "Map space detected.");
	}
}

static void	read_map_to_list(t_game *game, int map_fd)
{
	char	*line;
	int		is_map;

	is_map = 0;
	game->map.map_list = NULL;
	line = get_next_line(map_fd);
	while (line != NULL)
	{
		if (is_map == 0 && check_line(line) == TRUE)
			is_map = 1;
		if (is_map == 1)
			map_to_lst(game, map_fd, line);
		if (is_map == 0)
			free(line);
		line = get_next_line(map_fd);
	}
	if (game->player_x == -1 || game->player_y == -1)
		(close(map_fd), fatal_quit(game, "No player on the map file!"));
	if (is_map == 0 || game->map.map_list == NULL)
		(close(map_fd), fatal_quit(game, "Map is empty."));
	free(line);
}

static void	map_padding(t_game *game, char *line, int *index, int i)
{
	int	new_size;
	int	i_line;

	i_line = 0;
	new_size = game->map.size_x + 2;
	game->map.map[*index][i] = '*';
	i++;
	while (i < new_size && line[i_line] != '\0' && line[i_line] != '\n')
	{
		if (line[i_line] == ' ')
			game->map.map[*index][i] = '*';
		else
			game->map.map[*index][i] = line[i_line];
		i++;
		i_line++;
	}
	game->map.map[*index][i] = '*';
	while (i < new_size)
	{
		game->map.map[*index][i] = '*';
		i++;
	}
}

static void	alloc_map(void *content, void *param, int *index)
{
	char	*line;
	t_game	*game;
	int		i;
	int		new_size;

	i = 0;
	line = (char *)content;
	game = (t_game *)param;
	new_size = game->map.size_x + 2;
	game->map.map[*index] = (char *)ft_calloc(new_size + 3, sizeof(char));
	if (!game->map.map[*index])
		fatal_quit(game, "Map alloc failed.");
	if (*index == 0 || *index == game->map.size_y + 1)
	{
		while (i < new_size)
		{
			game->map.map[*index][i] = '*';
			i++;
		}
	}
	else
		map_padding(game, line, index, i);
	*index = *index + 1;
}

void	parse_map(t_game *game, int map_fd)
{
	int		y;
	t_list	*top_node;
	t_list	*bottom_node;

	y = 0;
	if (map_fd < 0)
		(close(map_fd), fatal_quit(game, "Map not found."));
	game->player_x = -1;
	game->player_y = -1;
	read_map_to_list(game, map_fd);
	game->map.size_x = 0;
	game->map.size_y = 0;
	ft_lstiter(game->map.map_list, calc_max_dimension, (void *)game, 0);
	game->map.map = (char **)ft_calloc(game->map.size_y + 3, sizeof(char *));
	if (!game->map.map)
		(close(map_fd), fatal_quit(game, "Map alloc failed."));
	top_node = ft_lstnew(NULL);
	bottom_node = ft_lstnew(NULL);
	ft_lstadd_front(&game->map.map_list, top_node);
	ft_lstadd_back(&game->map.map_list, bottom_node);
	ft_lstiter(game->map.map_list, alloc_map, (void *)game, &y);
	validate_map(game);
	close(map_fd);
}
