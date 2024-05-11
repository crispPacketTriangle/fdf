CC=cc -g
FLAGS=-Wall -Werror -Wextra
NAME=fdf
EXT=-L ./libft/ -L ./minilibx-linux/ -Lmlx_Linux -lft -lmlx -lXext -lX11 -lz -lm
LOGO=~/42/fdf/logo.sh
SRCS=fdf.c fdf_utils0.c fdf_utils1.c fdf_utils2.c fdf_utils3.c fdf_utils4.c
OBJS= $(SRCS:.c=.o)

all: deps $(NAME)
		@if [ -f $(LOGO) ]; then \
			bash $(LOGO); \
		fi 
deps:
		$(MAKE) -C libft
		$(MAKE) -C minilibx-linux

$(NAME): $(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(EXT) $(FLAGS)

clean:
		rm -rf $(OBJS)

fclean: clean
		rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re deps
