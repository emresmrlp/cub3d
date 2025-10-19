#ifndef PARSE_H
# define PARSE_H

# include "game.h"
# include "debugger.h"
# include "../external/libft/libft.h"
# include <fcntl.h>
# define RED 0
# define GREEN 1
# define BLUE 2

void    set_color(t_game *game, int color, int *loc);
int     check_file(char *map_file);
int     check_line(char *line);
void	parse(t_game *game, int argc, char **argv);
void    parse_map(t_game *game, int map_fd);
int     validate_map(t_game *game);

void    which_line(t_game *game, char *line, int *i);
void	parse_path(t_game *game);


#endif