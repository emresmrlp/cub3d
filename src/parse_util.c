/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 03:40:25 by ysumeral          #+#    #+#             */
/*   Updated: 2025/11/21 19:29:43 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

int  check_file(char *path)
{
	char	*extension;
	int		fd;

	if (!path) // path is NULL?
		return (0);
	extension = ft_strrchr(path, '.'); // (test.cub -> .cub) or (test.txt -> .txt)
	if (!extension || ft_strncmp(extension, ".cub", 5) != 0
		|| (path == extension) || (*(extension - 1) == '/')) // extension is NULL? extension is just ".cub|0" (not test.cubA)? and path is not just ".cub"? controls
	{
		fatal_debug("file extension error");
		return (0);
	}
	fd = open(path, O_RDONLY); //path can open?
	if (fd < 0)
	{
		fatal_debug("file is not exist");
		return (0);
	}
	close(fd);
	return (1);
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
			(fatal_debug("map file is incorrect (in colors)"), fatal_quit(game));
		(*loc)++;
	}
	if (!ft_strncmp(game->texture.key, "F", 1))
		game->texture.floor_color[color] = rgb;
	else if (!ft_strncmp(game->texture.key, "C", 1))
		game->texture.ceiling_color[color] = rgb;
}
