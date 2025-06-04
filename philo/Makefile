CC      = cc
CFLAGS  = -Wall -Wextra -Werror

SRCS    = cleanup.c main.c monitor.c time.c init.c routine.c utils.c
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
