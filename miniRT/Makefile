# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/08 14:33:39 by csilva-f          #+#    #+#              #
#    Updated: 2023/12/04 19:56:07 by csilva-f         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror -g -O3 -march=native -fsanitize=address

MLX = mlx_linux
MLX_FLAGS = -L ./$(MLX) -lmlx -Ilmlx_linux -lXext -lX11 -lbsd
OS = $(shell uname)

ifeq ($(OS), Darwin)
	MLX = mlx_macos
	MLX_FLAGS = -L ./$(MLX) -lmlx -framework OpenGL -framework AppKit -lm
endif

LIBFT = ./libft/libft.a
COORD_VECTOR = ./coords_vectors/coords_vectors.a
LINK = -I./includes
RM = rm -rf
NAME = miniRT

SRCS =	srcs/main.c				srcs/check.c			srcs/lights_camera_checker.c \
		srcs/shape_checker.c	srcs/colors.c			srcs/file_reader.c \
		srcs/solid_lst.c		srcs/solid_lst_2.c 		srcs/coord_transform.c \
		srcs/collisions.c 		srcs/lightrays.c 		srcs/mlx_stuff.c \
		srcs/pixel_camera.c		srcs/reflection.c		srcs/initialize.c \
		srcs/clear.c			srcs/phong.c			srcs/color_op.c \
		srcs/menu.c				srcs/print_parser.c		srcs/collisions_2.c \
		srcs/alter_solid_dim.c	srcs/translations.c		srcs/solid_movs.c \
		srcs/solid_movs_2.c		srcs/key_hook.c			srcs/solid_rot.c \
		srcs/rotation.c			srcs/ang_calculate.c	srcs/coord_transform_2.c

SRCS_BONUS = srcs_bonus/alter_solid_dim_bonus.c			srcs_bonus/check_bonus.c			srcs_bonus/clear_bonus.c \
			 srcs_bonus/collisions_bonus.c				srcs_bonus/collisions_2_bonus.c		srcs_bonus/color_op_bonus.c \
			 srcs_bonus/colors_bonus.c					srcs_bonus/coord_transform_bonus.c	srcs_bonus/file_reader_bonus.c \
			 srcs_bonus/initialize_bonus.c				srcs_bonus/key_hook_bonus.c			srcs_bonus/lightrays_bonus.c \
			 srcs_bonus/lights_camera_checker_bonus.c	srcs_bonus/main_bonus.c				srcs_bonus/menu_bonus.c \
			 srcs_bonus/mlx_stuff_bonus.c				srcs_bonus/phong_bonus.c			srcs_bonus/pixel_camera_bonus.c \
			 srcs_bonus/print_parser_bonus.c			srcs_bonus/reflection_bonus.c		srcs_bonus/rotation_bonus.c \
			 srcs_bonus/shape_checker_bonus.c			srcs_bonus/solid_lst_bonus.c		srcs_bonus/solid_lst_2_bonus.c \
			 srcs_bonus/solid_movs_bonus.c				srcs_bonus/solid_movs_2_bonus.c		srcs_bonus/solid_rot_bonus.c \
			 srcs_bonus/translations_bonus.c			srcs_bonus/ang_calculate_bonus.c	srcs_bonus/coord_transform_2_bonus.c \
			 srcs_bonus/solid_lst_3_bonus.c				srcs_bonus/collisions_3_bonus.c		srcs_bonus/solid_movs_3_bonus.c \
			 srcs_bonus/translations_2_bonus.c			srcs_bonus/rotation_2_bonus.c		srcs_bonus/light_lst_bonus.c \
			 srcs_bonus/solid_lst_4_bonus.c				srcs_bonus/solid_lst_5_bonus.c		srcs_bonus/collisions_bump.c \
			 srcs_bonus/lights_iterate_bonus.c			srcs_bonus/color_op_2_bonus.c		srcs_bonus/phong_2_bonus.c \
			 srcs_bonus/collisions_4_bonus.c

OBJ_DIR = obj
OBJS = $(SRCS:%.c=%.o)

OBJS_BONUS_DIR = obj_bonus
OBJS_BONUS = $(SRCS_BONUS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(COORD_VECTOR)
	$(info Compiling miniRT)
	$(MAKE) -C ./$(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(COORD_VECTOR) $(MLX_FLAGS) -lm -o $(NAME)

bonus: $(OBJS_BONUS) $(LIBFT) $(COORD_VECTOR)
	$(info Compiling miniRT_Bonus)
	$(MAKE) -C ./$(MLX)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT) $(COORD_VECTOR) $(MLX_FLAGS) -lm -o $(NAME)

$(LIBFT):
	$(MAKE) -C ./libft

$(COORD_VECTOR):
	$(MAKE) -C ./coords_vectors

clean:
	$(RM) $(OBJ_DIR) $(OBJS) $(OBJS_BONUS_DIR) $(OBJS_BONUS)
	$(MAKE) clean -C ./libft
	$(MAKE) clean -C ./coords_vectors

fclean: clean
	$(RM) $(NAME) $(BONUS)
	$(MAKE) fclean -C ./libft
	$(MAKE) fclean -C ./coords_vectors

re: fclean all
	$(MAKE) re -C ./libft
	$(MAKE) re -C ./coords_vectors

run: fclean all
	echo ""
	./$(NAME) ./$(BONUS) $(TEST_FILE)

noleaks: fclean all
	echo ""
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) ./$(BONUS)

.SILENT:

