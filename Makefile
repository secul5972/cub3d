# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chaekim <chaekim@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/03 12:57:22 by seungcoh          #+#    #+#              #
#    Updated: 2022/08/11 14:08:17 by chaekim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
RM = rm -f
#CFLAGS = -Wall -Wextra -Werror
MLX = -Lmlx -lmlx -framework OpenGL -framework Appkit

NAME = cub3d
SRCS = main.c parsing.c readmap.c utils.c\
	ft_function/ft_split.c ft_function/ft_utils.c\
	ft_function/ft_atoi.c find_pos.c get_ray.c
	   
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