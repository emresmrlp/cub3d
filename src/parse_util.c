/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 03:40:25 by ysumeral          #+#    #+#             */
/*   Updated: 2025/11/27 14:02:28 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

void	check_invalid_char(t_game *game, int map_fd, char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
	{
		if (line[i] != ' ' && line[i] != '1' && line[i] != '0'
			&& line[i] != 'N' && line[i] != 'S' && line[i] != 'E'
			&& line[i] != 'W')
			(close(map_fd), fatal_quit(game, "Invalid character."));
		else if (line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
		{
			if (game->player_x != -1 && game->player_y != -1)
				(close(map_fd), fatal_quit(game, "Multiple player."));
			game->player_x = 0;
			game->player_y = 0;
		}
		i++;
	}
}

void	calc_max_dimension(void *content, void *param, int *index)
{
	char	*line;
	int		len;
	t_game	*game;

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

void	check_file(t_game *game, char *path)
{
	char	*extension;
	int		fd;

	if (!path)
		fatal_quit(game, "Path is not correct.");
	extension = ft_strrchr(path, '.');
	if (!extension || ft_strncmp(extension, ".cub", 5) != 0
		|| (path == extension) || (*(extension - 1) == '/'))
		fatal_quit(game, "Extension is not correct.");
	fd = open(path, O_RDONLY);
	if (fd < 0)
		fatal_quit(game, "File is not exist.");
	close(fd);
}

int	check_line(char *line)
{
	int	i;

	if (!ft_strncmp(line, "\n", 1) || !ft_strncmp(line, " \n", 2))
		return (FALSE);
	i = 0;
	while (*(line + i) != '\0' && (*(line + i) == ' ' || *(line + i) == '\n'))
		i++;
	if (*(line + i) == '\0')
		return (FALSE);
	return (TRUE);
}

int	set_color(t_game *game, int color, int *loc)
{
	int	rgb;

	rgb = ft_atol(game->texture.value + *loc);
	if (rgb < 0 || rgb > 255 || ft_strlen(game->texture.value + *loc) <= 1)
		rgb = -1;
	while (*(game->texture.value + *loc) != '\0'
		&& ft_isdigit(*(game->texture.value + *loc)))
		(*loc)++;
	if (color < BLUE)
	{
		if (*(game->texture.value + *loc) != ',')
			return (FALSE);
		(*loc)++;
	}
	if (!ft_strncmp(game->texture.key, "F", 1))
		game->texture.floor_color[color] = rgb;
	else if (!ft_strncmp(game->texture.key, "C", 1))
		game->texture.ceiling_color[color] = rgb;
	return (TRUE);
}
