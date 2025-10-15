/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkayadib <zkayadib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 21:16:05 by zulfiye           #+#    #+#             */
/*   Updated: 2025/10/15 19:10:38 by zkayadib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

static void	assign_texture_path_we_ea(t_game *game, char *key, char *path)
{
	if (!ft_strncmp(key, "WE", 2))
	{
		if (game->texture.we_path)
			(free(path), fatal_debug("Faulty map!"),
				fatal_quit(game));
		else
			game->texture.we_path = path;
	}
	else if (!ft_strncmp(key, "EA", 2))
	{
		if (game->texture.ea_path)
			(free(path), fatal_debug("Faulty map!"),
				fatal_quit(game));
		else
			game->texture.ea_path = path;
	}
}

static void	assign_texture_path(t_game *game, char *key, char *path)
{
	if (!ft_strncmp(key, "NO", 2))
	{
		if (game->texture.no_path)
			(free(path), fatal_debug("Faulty map!"),
				fatal_quit(game));
		else
			game->texture.no_path = path;
	}
	else if (!ft_strncmp(key, "SO", 2))
	{
		if (game->texture.so_path)
			(free(path), fatal_debug("Faulty map!"),
				fatal_quit(game));
		else
			game->texture.so_path = path;
	}
	else
	{
		assign_texture_path_we_ea(game, key, path);
	}
}

void	parse_path(t_game *game, char *key, char *value)
{
	int		i;
	int		start;
	char	*path;

	i = 0;
	while (value[i] != '\0' && (value[i] == ' ' || value[i] == '\t'))
		i++;
	if (value[i] == '\0' || value[i] == '\n')
		(fatal_debug("map path is empty"), fatal_quit(game));
	start = i;
	while (value[i] != '\0' && value[i] != ' '
		&& value[i] != '\n' && value[i] != '\t')
		i++;
	path = ft_substr(value, start, i - start);
	if (!path)
		(fatal_debug("malloc error in parse_path"), fatal_quit(game));
	assign_texture_path(game, key, path);
	while (value[i] == ' ' || value[i] == '\t')
		i++;
	if (value[i] != '\0' && value[i] != '\n')
		(fatal_debug("invalid syntax in map (extra content after path)"),
			fatal_quit(game));
}

char	*which_line(t_game *game, char *line, int *i)
{
	char	*key;
	int		key_len;

	while (line[*i] != '\0' && line[*i] == ' ')
		(*i)++;
	if (ft_strchr("NSWEFC", line[*i]) == NULL)
		return (NULL);
	if (line[*i + 1] == ' ' || line[*i + 1] == '\t')
		key_len = 1;
	else
		key_len = 2;
	key = ft_substr(line, *i, key_len);
	if (!key)
		(fatal_debug("malloc error on key"), fatal_quit(game));
	if (ft_strncmp(key, "NO", 2) && ft_strncmp(key, "SO", 2)
	&& ft_strncmp(key, "WE", 2) && ft_strncmp(key, "EA", 2)
	&& ft_strncmp(key, "F", 1) && ft_strncmp(key, "C", 1))
	{
		free(key);
		(fatal_debug("invalid identifier in map file"), fatal_quit(game));
	}
	*i += key_len;
	return (key);
}