/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 16:43:17 by ysumeral          #+#    #+#             */
/*   Updated: 2025/11/22 22:31:45 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "game.h"
# include "../external/libft/libft.h"
# include <fcntl.h>
# define RED 0
# define GREEN 1
# define BLUE 2

int		set_color(t_game *game, int color, int *loc);
void	check_file(t_game *game, char *path);
int		check_line(char *line);
void	parse(t_game *game, int argc, char **argv);
void	parse_map(t_game *game, int map_fd);
void	validate_map(t_game *game);
void	calc_max_dimension(void *content, void *param, int *index);
void	which_line(t_game *game, char *line, int *i);
int		parse_path(t_game *game);
void	check_invalid_char(t_game *game, int map_fd, char *line);

#endif