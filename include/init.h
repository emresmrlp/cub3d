/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zulfiye <zulfiye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 16:42:14 by ysumeral          #+#    #+#             */
/*   Updated: 2025/11/22 15:32:08 by zulfiye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "game.h"
# include "debugger.h"
#include <sys/time.h>

# define IMG_HEIGHT 64
# define IMG_WIDTH 64

void	init(t_game *game);
void	init_player(t_game *game);

#endif