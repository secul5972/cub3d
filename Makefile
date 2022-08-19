# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seungcoh <seungcoh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/11 15:04:40 by seungcoh          #+#    #+#              #
#    Updated: 2022/08/17 16:10:12 by seungcoh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
MLX = -Lmlx -lmlx -framework OpenGL -framework Appkit -lm 

NAME = cub3D
SRCS = src/main.c src/parsing.c src/parsing2.c src/parsing3.c\
	src/read_map.c src/read_map2.c src/find_pos.c\
	src/utils.c src/utils2.c\
	src/ray_casting.c src/dda.c src/key_press.c src/key_press2.c\
	src/ft_function/ft_split.c src/ft_function/ft_utils.c\
	src/ft_function/ft_atoi.c
SRCS_BONUS = src_bonus/main_bonus.c src_bonus/parsing_bonus.c src_bonus/parsing2_bonus.c src_bonus/parsing3_bonus.c\
	src_bonus/read_map_bonus.c src_bonus/read_map2_bonus.c src_bonus/find_pos_bonus.c\
	src_bonus/utils_bonus.c src_bonus/utils2_bonus.c\
	src_bonus/ray_casting_bonus.c src_bonus/dda_bonus.c src_bonus/key_press_bonus.c src_bonus/key_press2_bonus.c\
	src_bonus/ft_function_bonus/ft_split_bonus.c src_bonus/ft_function_bonus/ft_utils_bonus.c\
	src_bonus/ft_function_bonus/ft_atoi_bonus.c

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:%.c=%.o)

ifdef WITH_BONUS
	OBJ_FILES = $(OBJS_BONUS)
else
	OBJ_FILES = $(OBJS)
endif

all: 		$(NAME)

$(NAME): 	$(OBJ_FILES)
			make -C mlx
			$(CC) $(CFLAGS) $(MLX) -o $(NAME) $(OBJ_FILES) -O3
clean:
			$(RM) $(OBJS) $(OBJS_BONUS)

fclean: 	clean
			make clean -C mlx
			$(RM) $(NAME)

re:			fclean all

bonus:
			make WITH_BONUS=1 all

.PHONY:		all clean fclean re