CC      = cc
CFLAGS  = -Wall -Wextra -Werror

SRCS    = main.c tools.c
OBJS    = $(SRCS:.c=.o)

HEADERS = philo.h
NAME    = philo

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
