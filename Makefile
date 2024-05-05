CC=cc
FLAGS=-Wall -Werror -Wextra
NAME=fdf
EXT=-L ./lib/ -L ./minilibx-linux/ -Lmlx_Linux -lft -lmlx -lXext -lX11 -lz -lm
LOGO=bash logo.sh

SRCS=fdf.c fdf_utils0.c fdf_utils1.c fdf_utils2.c fdf_utils3.c

OBJS= $(SRCS:.c=.o)

CPT="<C><P><T>" 

all: $(NAME)
		$(LOGO)

$(NAME): $(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(EXT) $(FLAGS)

clean:
		rm -rf $(OBJS)

fclean: clean
		rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
