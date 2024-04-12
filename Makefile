NAME = minishell

LIBFT = libft/libft.a
SRC_DIR = src/

CC = cc
CFLAGS = -Wall -Werror -Wextra -g
RM = rm -f


SRCS = 		$(SRC_DIR)test.c \
			$(SRC_DIR)error.c \
			$(SRC_DIR)free.c \
			$(SRC_DIR)init.c \
			$(SRC_DIR)lexer.c \
			$(SRC_DIR)parse_utils.c \
			$(SRC_DIR)parser.c \
			$(SRC_DIR)utils.c \
			$(SRC_DIR)token_list_utils.c \
			$(SRC_DIR)exec.c \
			$(SRC_DIR)expander.c \
			$(SRC_DIR)expander_utils.c \
			$(SRC_DIR)expander_utils2.c \
			$(SRC_DIR)env_list_utils.c \
			$(SRC_DIR)env.c \
			$(SRC_DIR)buildins.c \
			$(SRC_DIR)syntax_check.c \
			libft/get_next_line.c \
			libft/get_next_line_utils.c \
			# $(SRC_DIR)error.c \


OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lreadline $(LIBFT) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY:	all clean fclean re
