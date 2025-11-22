/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 03:40:25 by ysumeral          #+#    #+#             */
/*   Updated: 2025/11/22 18:15:33 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

void  check_file(t_game *game, char *path)
{
	char	*extension;
	int		fd;

	if (!path) // path is NULL?
		fatal_quit(game, "Path is not correct.");
	extension = ft_strrchr(path, '.'); // (test.cub -> .cub) or (test.txt -> .txt)
	if (!extension || ft_strncmp(extension, ".cub", 5) != 0
		|| (path == extension) || (*(extension - 1) == '/')) // extension is NULL? extension is just ".cub|0" (not test.cubA)? and path is not just ".cub"? controls
		fatal_quit(game, "Extension is not correct.");
	fd = open(path, O_RDONLY); //path can open?
	if (fd < 0)
		fatal_quit(game, "File is not exist.");
	close(fd);
}

int check_line(char *line)
{
	int i;

	if (!ft_strncmp(line, "\n", 1) || !ft_strncmp(line, " \n", 2))
		return (FALSE);
	i = 0;
	while (*(line + i) != '\0' && (*(line + i) == ' ' || *(line + i) == '\n'))
		i++;
	if (*(line + i) == '\0')
		return (FALSE);
	return (TRUE);
}

void set_color(t_game *game, int color, int *loc)
{
	int rgb;

	rgb = ft_atoi(game->texture.value + *loc);
	while (*(game->texture.value + *loc) != '\0'
		&& ft_isdigit(*(game->texture.value + *loc)))
		(*loc)++;
	if (color < BLUE)
	{
		if (*(game->texture.value + *loc) != ',')
			fatal_quit(game, "Colors is in correct on the map file.");
		(*loc)++;
	}
	if (!ft_strncmp(game->texture.key, "F", 1))
		game->texture.floor_color[color] = rgb;
	else if (!ft_strncmp(game->texture.key, "C", 1))
		game->texture.ceiling_color[color] = rgb;
}
