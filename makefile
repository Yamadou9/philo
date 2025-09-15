NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

SRC = action.c ft_atoi.c get_set.c init.c main.c monitor.c parsing.c pthread2.c pthread.c time.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
