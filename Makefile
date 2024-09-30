NAME = miniRT

CC = gcc
FLAGS = -Wall -Wextra -Werror
RM = rm -rf

HEAD = libft/libft.h includes/get_next_line.h includes/MiniRT.h mlx_linux/mlx.h
SRCS = srcs/main.c srcs/get_next_line/get_next_line.c srcs/get_next_line/get_next_line_utils.c \
		srcs/parse/parse.c srcs/parse/parse_values.c srcs/operations/operations1.c srcs/parse/parse_utils.c \
		srcs/operations/operations2.c srcs/parse/check_input.c srcs/parse/check_utils.c srcs/parse/parse_utils2.c \
		srcs/intersections/op_intersections.c srcs/intersections/check_intersections.c srcs/intersections/intersection_utils.c\
		srcs/mlx_functional/hook.c srcs/mlx_functional/colors.c \
		srcs/colors/colorize.c srcs/colors/color_utils.c \
		srcs/colors/colors_parse/colors_parse.c \
		srcs/colors/shadows/calc_shadows.c 

OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

all : libs $(NAME)

%.o : %.c Makefile $(HEAD)
	$(CC) $(FLAGS) -I/usr/include -Imlx_linux -MMD -c $< -o $@

libs:
	make -C libft
	make -C mlx_linux

$(NAME): $(OBJS) 
	$(CC) $(FLAGS) $(OBJS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -o $(NAME) -Llibft -lft

clean :
	make clean -C libft
	make clean -C mlx_linux
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	make fclean -C libft
	$(RM) $(NAME)

re : fclean all

-include $(DEPS)

.PHONY : all clean fclean re libs