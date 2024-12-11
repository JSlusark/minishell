NAME = minishell
LIBFT = libft/libft.a

TOKENIZATION  = ./parsing/tokens/return_tokens.c \
				./parsing/tokens/mock_tokens.c

NODE_CREATION = 	./parsing/nodes/return_nodes.c \
					./parsing/nodes/error_handling.c \
					./parsing/nodes/alloc_nodes.c \
					./parsing/nodes/alloc_redir.c \
					./parsing/nodes/alloc_cmd.c \
					./parsing/nodes/alloc_option.c \
					./parsing/nodes/alloc_args.c \
					./parsing/nodes/free_nodes.c \
					./parsing/nodes/print_nodes.c

EXECUTION	= ./execution/execution.c

SRC	= $(TOKENIZATION) \
	$(NODE_CREATION) \
	$(EXECUTION)

HEADERS	= ./minishell.h \

OBJS = $(SRC:.c=.o)

CC	= cc

RM	= rm -f

CFLAGS	= -Wall -Wextra -Werror -I./include -I./libft -g
PFLAGS = -lreadline

all:	$(LIBFT) $(NAME)

$(LIBFT):
		@make -C libft

$(NAME):	$(OBJS) $(HEADERS) $(LIBFT)
		$(CC) $(CFLAGS) main.c -o $(NAME) $(OBJS) $(LIBFT) $(PFLAGS)

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
