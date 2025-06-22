CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g -pthread

NAME = philo
SRCS = init.c  main.c  routine.c  utils1.c  utils2.c utils3.c
OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
