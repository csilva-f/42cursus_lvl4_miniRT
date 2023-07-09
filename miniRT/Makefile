# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/08 14:33:39 by csilva-f          #+#    #+#              #
#    Updated: 2023/07/08 15:03:05 by csilva-f         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := miniRT
BONUS := miniRT_bonus

CC := cc
CFLAGS := -Wall -Werror -Wextra -O3
LFLAGS := -L ./srcs/minilibx-linux -lmlx -Ilmlx -lXext -lX11 -lm

ifdef DEBUG
		CFLAGS += -fsanitize=address
endif

SRCS :=		srcs/main.c							srcs/ft_check.c			

SRCS_BONUS := 

OBJ_FOLDER := obj

OBJS := $(SRCS:.c=.o)

OBJS_BONUS := $(SRCS_BONUS:.c=.o)

TARGET = $($(OBJ_FOLDER)/, $(OBJS))

LIBFT := srcs/libft/libft.a

all:	$(NAME)

$(NAME):	$(OBJS) $(OBJ_FOLDER) $(TARGET) $(LIBFT) $(MINILIBX)
			$(CC) $(CFLAGS) $(LFLAGS) $(TARGET) $(LIBFT) $(MINILIBX) -o $(NAME)
			echo "\033[1m $(NAME) ready \033[0m"


bonus:	$(BONUS)

$(BONUS):	$(OBJS_BONUS) $(LIBFT) $(MINILIBX)
			$(CC) $(CFLAGS) -lm $(OBJS_BONUS) $(LFLAGS) $(LIBFT) $(MINILIBX) -o $(BONUS)
			echo "\033[1m $(BONUS) ready \033[0m"

clean:
		rm -rf $(OBJS)
		rm -rf $(OBJS_BONUS)
		rm -rf $(OBJS_FOLDER)
		echo "OBJS deleted"

fclean:	clean
		rm -rf $(NAME)
		rm -rf $(BONUS)
		echo "$(NAME) deleted"
		echo "$(BONUS) deleted"

re:	fclean all

.SILENT:
