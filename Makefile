# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zkayadib <zkayadib@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/28 20:23:36 by ysumeral          #+#    #+#              #
#    Updated: 2025/10/02 21:01:01 by zkayadib         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -I${INC_DIR}
SRC_DIR = ./src
GNL_DIR = ./external
MLX_DIR = ./mlx
INC_DIR = ./include
MLX = -L$(MLX_DIR) -lmlx -lX11 -lXext
SRC =	$(SRC_DIR)/main.c \
		$(SRC_DIR)/debugger.c \
		$(SRC_DIR)/memory.c \
		$(SRC_DIR)/input.c \
		$(SRC_DIR)/draw.c \
		$(SRC_DIR)/parse.c \
		$(SRC_DIR)/init.c \
		$(SRC_DIR)/game.c
GNL =	$(GNL_DIR)/get_next_line.c \
		$(GNL_DIR)/get_next_line_utils.c
OBJ = $(SRC:.c=.o)
OBJ_GNL = $(GNL:.c=.o)
NAME = cub3D

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_GNL)
	make -C $(MLX_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(OBJ_GNL) ${PRINTF_LIB} $(MLX)

clean:
	rm -f $(OBJ) $(OBJ_GNL)

fclean: clean
	make -C $(MLX_DIR) clean
	rm -f $(NAME)

re: fclean all

ex: all clean

.PHONY: all clean fclean re