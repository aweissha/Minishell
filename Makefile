NAME = minishell

LIBFT = libft/libft.a
SRC_DIR = src/

CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f


SRCS = 		$(SRC_DIR)minishell.c \
			$(SRC_DIR)init.c \
			$(SRC_DIR)error.c \


OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) -lreadline $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY:	all clean fclean re
