NAME= cub3d
SRC = main.c parsing.c parsing2.c read_map.c read_map2.c\
	utils.c utils2.c ray_casting.c dda_algo.c key_press.c\
	ft_function/ft_split.c ft_function/ft_utils.c\
	ft_function/ft_atoi.c find_pos.c
OBJ = $(SRC:%.c=%.o)

MLX_DIR = ./minilibx-linux
LFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd

RM = rm -f
CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LFLAGS)

%.o: %.c
	$(CC) -I$(MLX_DIR) -c -o $@ $<

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

bonus: $(OBJ_BONUS)
	$(CC) $(CFLAGS) -o $(NAME) $^

.PHONY: all clean fclean re bonus