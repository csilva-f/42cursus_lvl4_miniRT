# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/08 14:33:39 by csilva-f          #+#    #+#              #
#    Updated: 2023/07/09 17:02:00 by csilva-f         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OS = $(shell uname)
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

ifeq ($(OS), Linux)
	CFLAGS += -D OS_LINUX
	MLX_FLAGS = -L ./mlx_linux -lmlx -Ilmlx_linux -lXext -lX11 -lbsd
else
	CFLAGS += -D OS_MACOS
	MLX_FLAGS = -L ./mlx_macos -lmlx -framework OpenGL -framework AppKit
endif

LIBFT = ./libft/libft.a
LINK = -I./includes
RM = rm -rf
NAME = miniRT

SRCS = srcs/main.c 				srcs/ft_check.c

OBJ_DIR = obj
OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(info Compiling miniRT for $(OS))
ifeq ($(OS), Linux)
	$(MAKE) -C ./mlx_linux
else
	$(MAKE) -C ./mlx_macos
endif
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -lm -o $(NAME)

$(LIBFT):
	$(MAKE) -C ./libft

clean:
	$(RM) $(OBJ_DIR) $(OBJS) 
	$(MAKE) clean -C ./libft

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C ./libft

re: fclean all
	$(MAKE) re -C ./libft

run: fclean all
	echo ""
	./$(NAME) $(TEST_FILE)

noleaks: fclean all
	echo ""
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

.SILENT:

.PHONY: all miniRT clean fclean re obj
