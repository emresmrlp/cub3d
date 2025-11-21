/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugger.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 16:39:16 by ysumeral          #+#    #+#             */
/*   Updated: 2025/11/21 16:39:20 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUGGER_H
# define DEBUGGER_H

# include "game.h"
# include "../external/mlx/mlx.h"

void	debug(char *msg);
void	fatal_debug(char *msg);

#endif