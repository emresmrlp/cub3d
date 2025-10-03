/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:47:01 by ysumeral          #+#    #+#             */
/*   Updated: 2025/10/03 16:58:42 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/calc.h"

static int	width(int *counter, char *line)
{
	int	len;

	len = 0;
	while (line[len] != '\0')
		len++;
	if (*(line + len - 1) == '\n')
		len = len - 1;
	if (*counter == 0)
		*counter = len;
	else if (*counter < len)
		*counter = len;
	return (0);
}

static int	height(int *counter, char *line)
{
	(void)line;
	(*counter)++;
	return (0);
}

static int	calc_size(const char *map_path, int (*f)(int*, char*))
{
	int		fd;
	int		counter;
	char	*line;

	counter = 0;
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (-1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (f(&counter, line))
		{
			free(line);
			close(fd);
			return (-1);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (counter);
}

int calc_max(const char *map_path, char direction)
{
	if (direction == 'x')
		return (calc_size(map_path, width));
	else if (direction == 'y')
		return (calc_size(map_path, height));
	else
		return (-1);
}