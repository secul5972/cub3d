NAME = cub3D
SRC = src/main.c src/parsing.c src/parsing2.c src/parsing3.c\
	src/read_map.c src/read_map2.c src/find_pos.c\
	src/utils.c src/utils2.c\
	src/ray_casting.c src/dda.c src/key_press.c src/key_press2.c\
	src/ft_function/ft_split.c src/ft_function/ft_utils.c\
	src/ft_function/ft_atoi.c
OBJ = $(SRC:%.c=%.o)

SRC_BONUS = src_bonus/main_bonus.c src_bonus/parsing_bonus.c src_bonus/parsing2_bonus.c src_bonus/parsing3_bonus.c\
	src_bonus/read_map_bonus.c src_bonus/read_map2_bonus.c src_bonus/find_pos_bonus.c\
	src_bonus/utils_bonus.c src_bonus/utils2_bonus.c\
	src_bonus/ray_casting_bonus.c src_bonus/dda_bonus.c src_bonus/key_press_bonus.c src_bonus/key_press2_bonus.c\
	src_bonus/ft_function_bonus/ft_split_bonus.c src_bonus/ft_function_bonus/ft_utils_bonus.c\
	src_bonus/ft_function_bonus/ft_atoi_bonus.c
OBJ_BONUS = $(SRC_BONUS:%.c=%.o)

MLX_DIR = ./minilibx-linux
LFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd

RM = rm -f
CC = gcc
CFLAGS = -Wall -Wextra -Werror

ifdef WITH_BONUS
	OBJ_FILES = $(OBJ_BONUS)
else
	OBJ_FILES = $(OBJ)
endif

all: $(NAME)

#$(NAME): $(OBJ)
#	$(CC) -o $(NAME) $(OBJ) $(LFLAGS)
$(NAME): $(OBJ_FILES)
	$(CC) -o $(NAME) $^ $(LFLAGS)

%.o: %.c
	$(CC) -I$(MLX_DIR) -c $< -o $@

clean:
	$(RM) $(OBJ) $(OBJ_BONUS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

bonus:
	make WITH_BONUS=1 all

.PHONY: all clean fclean re bonus