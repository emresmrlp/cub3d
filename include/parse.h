#ifndef PARSE_H
# define PARSE_H

# include "game.h"
# include "debugger.h"
# include "calc.h"
# include <fcntl.h>
#include "../external/libft/libft.h"
# define RED 0
# define GREEN 1
# define BLUE 2

char    *ft_substr(char const *s, unsigned int start, size_t len);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
int     ft_atoi(const char *str);
int     ft_isdigit(int c);
char    *ft_strrchr(const char *s, int c);

void    set_color(t_game *game, int color, char *key, char *value, int *loc);
int     check_file(char *map_file);
int     check_line(char *line);
void	parse(t_game *game, int argc, char **argv);
void	find_map(t_game *game, int fd);

char	*which_line(t_game *game, char *line, int *i);
void	parse_path(t_game *game, char *key, char *value);


#endif