NAME = minishell

SRC	= main.c src.c

HEADERS	= ./include/minishell.h

OBJS	= $(SRC:.c=.o)

CC	= cc

RM	= rm -f

CFLAGS	= -Wall -Wextra -Werror -I./include
PFLAGS = -lreadline

all:	$(NAME)

$(NAME):	$(OBJS) $(HEADERS)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(PFLAGS)

.c.o:
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
