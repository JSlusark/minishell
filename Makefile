NAME = minishell
LIBFT = libft/libft.a

MOCK_TOKENS = ./mock_data/create_mock_tokens.c

SRC	= main.c \
	parsing.c \
	parsing_free.c \
	print_nodes.c \
	exec_test.c \
	$(MOCK_TOKENS)


HEADERS	= ./include/minishell.h \
		./include/token.h \
		./include/node.h

OBJS	= $(SRC:.c=.o)

CC	= cc

RM	= rm -f

CFLAGS	= -Wall -Wextra -Werror -I./include -I./libft
PFLAGS = -lreadline

all:	$(LIBFT) $(NAME)

$(LIBFT):
		@make -C libft

$(NAME):	$(OBJS) $(HEADERS) $(LIBFT)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(PFLAGS)

.c.o:
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		$(RM) $(OBJS)
		@make -C libft clean

fclean:		clean
		$(RM) $(NAME)
		@make -C libft fclean

re:			fclean all

.PHONY:		all clean fclean re
