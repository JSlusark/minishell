NAME = minishell
LIBFT = libft/libft.a

TOKENIZATION  = ./parsing/tokenization/mock_tokens.c
NODE_CREATION = 	./parsing/node_creation/create_nodes.c \
					./parsing/node_creation/free_nodes.c \
					./parsing/node_creation/print_nodes.c
EXECUTION	= ./execution/execution.c

SRC	= main.c \
	$(TOKENIZATION) \
	$(NODE_CREATION) \
	$(EXECUTION)

HEADERS	= ./headers/minishell.h \
		./headers/token.h \
		./headers/node.h

OBJS = $(SRC:.c=.o)

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
