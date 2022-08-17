# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chaekim <chaekim@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/11 15:04:40 by seungcoh          #+#    #+#              #
#    Updated: 2022/08/17 13:02:09 by chaekim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc -g
RM = rm -f
#CFLAGS = -Wall -Wextra -Werror
MLX = -Lmlx -lmlx -framework OpenGL -framework Appkit -lm 

NAME = cub3d
SRCS = main.c parsing.c parsing2.c read_map.c read_map2.c\
	utils.c utils2.c ray_casting.c dda.c key_press.c key_press2.c\
	ft_function/ft_split.c ft_function/ft_utils.c\
	ft_function/ft_atoi.c find_pos.c
	   
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