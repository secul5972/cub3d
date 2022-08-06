# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seungcoh <seungcoh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/03 12:57:22 by seungcoh          #+#    #+#              #
#    Updated: 2022/08/03 13:45:18 by seungcoh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
RM = rm -f
#CFLAGS = -Wall -Wextra -Werror
MLX = -Lmlx -lmlx -framework OpenGL -framework Appkit

NAME = cub3d
SRCS = main.c parsing.c readmap.c utils.c\
	ft_function/ft_split.c ft_function/ft_utils.c\
	ft_function/ft_atoi.c
	   
OBJS = $(SRCS:.c=.o)

all: 		$(NAME)

$(NAME): 	$(OBJS)
			make -C mlx
			$(CC) $(CFLAGS) $(MLX) -o $(NAME) $(OBJS) -O3
clean:
			$(RM) $(OBJS)

fclean: 	clean
			make clean -C mlx
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re