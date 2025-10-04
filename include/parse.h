#ifndef PARSE_H
# define PARSE_H

# include "game.h"
# include "debugger.h"
# include "calc.h"
# include <fcntl.h>
# define RED 1
# define GREEN 2;
# define BLUE 3;

void    set_color(t_game *game, int color, char *key, char *value, int *loc);
int     check_file(char *map_file);
int     check_line(char *line);
void	parse(t_game *game, int argc, char **argv);

#endif