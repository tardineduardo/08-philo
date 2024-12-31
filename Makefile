MAIN =  src/philo.c \
		src/utils.c \
		src/args.c \
		src/inits.c	\
		src/actions.c \

OBJS_SRC =	$(MAIN:.c=.o)

CC = cc
RM = rm -f
#CFLAGS = -Wall -Wextra -Werror -g
CFLAGS = -g -pthread

NAME = philo

all: $(NAME)

$(NAME): $(OBJS_SRC)
		$(CC) $(CFLAGS) $(OBJS_SRC) -o $(NAME)

src/%.o: src/%.c
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		$(RM) $(OBJS_SRC)

fclean: clean
		$(RM) $(NAME) $(CHECK)

re: fclean all

.PHONY: all clean fclean re