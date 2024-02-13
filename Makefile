NAME = philosophers.out

CC = cc -g3
CFLAGS = -Wall -Wextra -Werror 

SRCS = 			src/main.c\
				src/ft_init.c\
				src/ft_routine_philo.c\

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) -lpthread

%.o: %.c include/philosophers.h
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJS) clean

fclean: clean
	rm -f $(NAME) fclean

re: fclean all

.PHONY: clean fclean re all