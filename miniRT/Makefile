# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/08 14:33:39 by csilva-f          #+#    #+#              #
#    Updated: 2023/08/29 19:48:05 by csilva-f         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

MLX_FLAGS = -L ./mlx_linux -lmlx -Ilmlx_linux -lXext -lX11 -lbsd

LIBFT = ./libft/libft.a
COORD_VECTOR = ./coords_vectors/coords_vectors.a
LINK = -I./includes
RM = rm -rf
NAME = miniRT

SRCS =	srcs/main.c					srcs/check.c					srcs/lights_camera_checker.c \
		srcs/shape_checker.c		srcs/colors.c					srcs/file_reader.c \
		srcs/solid_lst.c			srcs/solid_lst_2.c 				srcs/coord_transform.c \
		srcs/collisions.c 			srcs/lightrays.c 				srcs/mlx_stuff.c \
		srcs/pixel_camera.c			srcs/reflection.c				srcs/initialize.c \
		srcs/clear.c

OBJ_DIR = obj
OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(COORD_VECTOR)
	$(info Compiling miniRT)
	$(MAKE) -C ./mlx_linux
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(COORD_VECTOR) $(MLX_FLAGS) -lm -o $(NAME)

$(LIBFT):
	$(MAKE) -C ./libft

$(COORD_VECTOR):
	$(MAKE) -C ./coords_vectors

clean:
	$(RM) $(OBJ_DIR) $(OBJS) 
	$(MAKE) clean -C ./libft
	$(MAKE) clean -C ./coords_vectors

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C ./libft
	$(MAKE) fclean -C ./coords_vectors

re: fclean all
	$(MAKE) re -C ./libft
	$(MAKE) re -C ./coords_vectors

run: fclean all
	echo ""
	./$(NAME) $(TEST_FILE)

noleaks: fclean all
	echo ""
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

.SILENT:

.PHONY: all miniRT clean fclean re obj
