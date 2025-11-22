/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:43:49 by ysumeral          #+#    #+#             */
/*   Updated: 2025/11/22 17:56:07 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "game.h"

long	calc_time(void);
void	register_hooks(t_game *game);
void	move_forward(t_game *game);
void	move_backward(t_game *game);
void	move_left(t_game *game);
void	move_right(t_game *game);
int		event_click(void *param);
void	rotate_left(t_game *game);
void	rotate_right(t_game *game);

#endif