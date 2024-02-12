NAME = philosophers

CC = cc -g3
CFLAGS = -Wall -Wextra -Werror

SRCS = 			src/main.c\
				src/ft_init.c\

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

%.o: %.c include/philosophers.h
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJS) clean

fclean: clean
	rm -f $(NAME) fclean

re: fclean all

.PHONY: clean fclean re all