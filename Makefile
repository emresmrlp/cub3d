# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysumeral <ysumeral@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/28 20:23:36 by ysumeral          #+#    #+#              #
#    Updated: 2025/10/02 16:03:06 by ysumeral         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -I${INC_DIR}
SRC_DIR = ./src
MLX_DIR = ./mlx
INC_DIR = ./include
MLX = -L$(MLX_DIR) -lmlx -lX11 -lXext
SRC =	$(SRC_DIR)/main.c \
		$(SRC_DIR)/debugger.c \
		$(SRC_DIR)/memory.c \
		$(SRC_DIR)/input.c \
		$(SRC_DIR)/draw.c \
		$(SRC_DIR)/parse.c \
		$(SRC_DIR)/game.c
OBJ = $(SRC:.c=.o)
NAME = cub3D

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(MLX_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) ${PRINTF_LIB} $(MLX)

clean:
	rm -f $(OBJ)

fclean: clean
	make -C $(MLX_DIR) clean
	rm -f $(NAME)

re: fclean all

ex: all clean

.PHONY: all clean fclean re