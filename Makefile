# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zulfiye <zulfiye@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/28 20:23:36 by ysumeral          #+#    #+#              #
#    Updated: 2025/11/22 15:26:44 by zulfiye          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -I${INC_DIR}
SRC_DIR = ./src
LIBFT_LIB = ./external/libft/libft.a
LIBFT_DIR = ./external/libft
GNL_DIR = ./external/gnl
MLX_DIR = ./external/mlx
INC_DIR = ./include
MLX = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm
SRC =	$(SRC_DIR)/main.c \
		$(SRC_DIR)/debugger.c \
		$(SRC_DIR)/memory.c \
		$(SRC_DIR)/input.c \
		$(SRC_DIR)/parse_file.c \
		$(SRC_DIR)/parse_util.c \
		$(SRC_DIR)/parse_line.c \
		$(SRC_DIR)/parse_map.c \
		$(SRC_DIR)/validate_map.c \
		$(SRC_DIR)/init.c \
		$(SRC_DIR)/player.c \
		$(SRC_DIR)/raycast.c \
		$(SRC_DIR)/game.c	\
		$(SRC_DIR)/move.c	\
		$(SRC_DIR)/draw.c	\
		$(SRC_DIR)/raycast_utils.c	\
		$(SRC_DIR)/rotate_and_utils.c
GNL =	$(GNL_DIR)/get_next_line.c \
		$(GNL_DIR)/get_next_line_utils.c
OBJ = $(SRC:.c=.o)
OBJ_GNL = $(GNL:.c=.o)
NAME = cub3D

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_GNL)
	make bonus -C $(LIBFT_DIR)
	make -C $(MLX_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(OBJ_GNL) $(LIBFT_LIB) $(MLX)

clean:
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean
	rm -f $(OBJ) $(OBJ_GNL)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	make -C $(MLX_DIR) clean
	rm -f $(NAME)

re: fclean all

ex: all clean

.PHONY: all clean fclean re