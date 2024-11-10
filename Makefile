NAME = minishell
LIBFT = libft/libft.a

MOCK_DATA = mock_scan.c \
			mock_test.c \
			mock_tokens

SRC	= main.c \
	$(MOCK_DATA)

HEADERS	= ./include/minishell.h ./include/node.h ./include/scanner.h ./include/token.h

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
