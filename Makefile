CC=cc
# -Wall -Werror -Wextra
NAME=fdf
EXT=-L ./lib/ -lft -lmlx -lXext -lX11 -lm

SRCS=fdf.c fdf_utils.c

OBJS= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(EXT)

clean:
		rm -rf $(OBJS)

fclean: clean
		rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
