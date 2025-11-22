/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 16:42:14 by ysumeral          #+#    #+#             */
/*   Updated: 2025/11/22 20:46:39 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "game.h"

# define IMG_HEIGHT 64
# define IMG_WIDTH 64

void	init(t_game *game);
void	init_player(t_game *game);

#endif