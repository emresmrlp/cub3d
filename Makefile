#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysumeral < ysumeral@student.42istanbul.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/28 20:23:36 by ysumeral          #+#    #+#              #
#    Updated: 2025/09/28 20:27:09 by ysumeral         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC_DIR = ./src
MLX_DIR = ./mlx
INC_DIR = ./include
MLX = -L$(MLX_DIR) -lmlx -lX11 -lXext
SRC =	$(SRC_DIR)/main.c
OBJ = $(SRC:.c=.o)
NAME = cub3D

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(MLX_DIR)
	$(CC) $(CFLAGS) -I${INC_DIR} -o $(NAME) $(OBJ) ${PRINTF_LIB} $(MLX)

clean:
	rm -f $(OBJ)

fclean: clean
	make -C $(MLX_DIR) clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re