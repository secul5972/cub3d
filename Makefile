# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chaekim <chaekim@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/11 15:04:40 by seungcoh          #+#    #+#              #
#    Updated: 2022/08/11 15:11:24 by chaekim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
RM = rm -f
#CFLAGS = -Wall -Wextra -Werror
MLX = -Lmlx -lmlx -framework OpenGL -framework Appkit

NAME = cub3d
SRCS = main.c parsing.c read_map.c read_map2.c utils.c utils2.c\
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