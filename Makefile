# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/28 20:23:36 by ysumeral          #+#    #+#              #
#    Updated: 2025/10/04 03:39:34 by ysumeral         ###   ########.fr        #
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
MLX = -L$(MLX_DIR) -lmlx -lX11 -lXext
SRC =	$(SRC_DIR)/main.c \
		$(SRC_DIR)/debugger.c \
		$(SRC_DIR)/memory.c \
		$(SRC_DIR)/input.c \
		$(SRC_DIR)/draw.c \
		$(SRC_DIR)/parse.c \
		$(SRC_DIR)/init.c \
		$(SRC_DIR)/util.c \
		$(SRC_DIR)/calc.c \
		$(SRC_DIR)/game.c 
GNL =	$(GNL_DIR)/get_next_line.c \
		$(GNL_DIR)/get_next_line_utils.c
OBJ = $(SRC:.c=.o)
OBJ_GNL = $(GNL:.c=.o)
NAME = cub3D

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_GNL)
	make -C $(LIBFT_DIR)
	make -C $(MLX_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(OBJ_GNL) ${PRINTF_LIB} $(MLX)

clean:
	rm -f $(OBJ) $(OBJ_GNL)

fclean: clean
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean
	rm -f $(NAME)

re: fclean all

ex: all clean

.PHONY: all clean fclean re