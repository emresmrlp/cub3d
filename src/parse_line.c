/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 21:16:05 by zulfiye           #+#    #+#             */
/*   Updated: 2025/11/22 21:18:26 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

static void	assign_texture_path_util(t_game *game, char **dest_path, char *path)
{
	if (*dest_path)
	{
		free(path);
		path = NULL;
		fatal_quit(game, "Map is not correct!");
	}
	else
		*dest_path = path;
}

static void	assign_texture_path(t_game *game, char *key, char *path)
{
	char	**dest_path;

	dest_path = NULL;
	if (!ft_strncmp(key, "NO", 2))
		dest_path = &game->texture.no_path;
	else if (!ft_strncmp(key, "SO", 2))
		dest_path = &game->texture.so_path;
	else if (!ft_strncmp(key, "WE", 2))
		dest_path = &game->texture.we_path;
	else if (!ft_strncmp(key, "EA", 2))
		dest_path = &game->texture.ea_path;
	else
	{
		free(path);
		return ;
	}
	assign_texture_path_util(game, dest_path, path);
}

int	parse_path(t_game *game)
{
	int		i;
	int		start;
	char	*path;

	i = 0;
	while (game->texture.value[i] != '\0' && (game->texture.value[i] == ' '
			|| game->texture.value[i] == '\t'))
		i++;
	if (game->texture.value[i] == '\0' || game->texture.value[i] == '\n')
		return (FALSE);
	start = i;
	while (game->texture.value[i] != '\0' && game->texture.value[i] != ' '
		&& game->texture.value[i] != '\n' && game->texture.value[i] != '\t')
		i++;
	path = ft_substr(game->texture.value, start, i - start);
	if (!path)
		return (FALSE);
	assign_texture_path(game, game->texture.key, path);
	while (game->texture.value[i] == ' ' || game->texture.value[i] == '\t')
		i++;
	if (game->texture.value[i] != '\0' && game->texture.value[i] != '\n')
		return (FALSE);
	return (TRUE);
}

static void	direction_text_init(t_game *game, char *line)
{
	if (ft_strncmp(game->texture.key, "NO", 2)
		&& ft_strncmp(game->texture.key, "SO", 2)
		&& ft_strncmp(game->texture.key, "WE", 2)
		&& ft_strncmp(game->texture.key, "EA", 2))
		(free(line), fatal_quit(game, "Invalid identifier."));
}

void	which_line(t_game *game, char *line, int *i)
{
	int		key_len;

	if (game->texture.key)
		(free(game->texture.key), game->texture.key = NULL);
	while (line[*i] != '\0' && line[*i] == ' ')
		(*i)++;
	if (ft_strchr("NSWEFC", line[*i]) == NULL)
		return ;
	if (line[*i + 1] == ' ' || line[*i + 1] == '\t')
		key_len = 1;
	else
		key_len = 2;
	game->texture.key = ft_substr(line, *i, key_len);
	if (!game->texture.key)
		(free(line), fatal_quit(game, "Key value alloc failed."));
	if (key_len == 1)
	{
		if (ft_strncmp(game->texture.key, "F", 1)
			&& ft_strncmp(game->texture.key, "C", 1))
			(free(line), fatal_quit(game, "Invalid identifier."));
	}
	else if (key_len == 2)
		direction_text_init(game, line);
	*i += key_len;
}
