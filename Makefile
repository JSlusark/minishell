# Makefile for the shell project

# Compiler and flags
CC := cc

# Original: Used for AddressSanitizer to detect memory corruption issues like buffer overflows.
CFLAGS := -Wall -Wextra -Werror -g -fsanitize=address
# # Updated: Added -fsanitize=leak for better memory leak detection since AddressSanitizer alone focuses more on buffer overflows.
# CFLAGS := -Wall -Wextra -Werror -g -fsanitize=address -fsanitize=leak
# # Used when running "make valgrind" as Valgrind cannot be used on binaries compiled with -fsanitize=address. Use MAKE VALGRIND to run (uncomment it at the bottomo of the page)
# CFLAGS := -Wall -Wextra -Werror -g

INCLUDE := -Iinclude -Ilib/libft -Ilib/dprintf

# Directories
SRC_DIR := src
OBJ_DIR := obj
LIB_DIR := lib
LIBFT_DIR := $(LIB_DIR)/libft
DPRINTF_DIR := $(LIB_DIR)/dprintf

LIBFT_OBJ_DIR := $(LIBFT_DIR)/obj
DPRINTF_OBJ_DIR := $(LIB_DIR)/dprintf

# Libraries
LIBFT := $(LIBFT_DIR)/libft.a
DPRINTF := $(DPRINTF_DIR)/libdprintf.a

# Executable name
NAME := minishell

# Source files and object files
SRC := $(shell find $(SRC_DIR) -type f -name "*.c")
OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# Rules
all: $(NAME)

$(NAME): $(LIBFT) $(DPRINTF) $(OBJ)
	@if [ ! -f $(LIBFT) ]; then \
		echo "Error: libft.a not found in $(LIBFT_DIR)"; exit 1; \
	fi
	@if [ ! -f $(DPRINTF) ]; then \
		echo "Error: libftdprintf.a not found in $(DPRINTF_DIR)"; exit 1; \
	fi
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(DPRINTF) -lreadline -o $(NAME)

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Build libft
$(LIBFT):
	$(MAKE) OBJ_DIR=$(LIBFT_OBJ_DIR) -C $(LIBFT_DIR)

# Build ft_dprintf
$(DPRINTF):
	@echo "Building libdprintf.a in $(DPRINTF_DIR)"
	$(MAKE) OBJ_DIR=$(DPRINTF_OBJ_DIR) -C $(DPRINTF_DIR)

# Clean rules
clean:
	$(MAKE) clean OBJ_DIR=$(LIBFT_OBJ_DIR) -C $(LIBFT_DIR)
	$(MAKE) clean OBJ_DIR=$(DPRINTF_OBJ_DIR) -C $(DPRINTF_DIR)
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) fclean OBJ_DIR=$(LIBFT_OBJ_DIR) -C $(LIBFT_DIR)
	$(MAKE) fclean OBJ_DIR=$(DPRINTF_OBJ_DIR) -C $(DPRINTF_DIR)
	rm -f $(NAME)

re: fclean all

## Added to use minishell with valgrind and avoid copy/past all the time - cannot be used when the program is compiled with fsanitise
# valgrind:
# 	valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all ./$(NAME)

.PHONY: all clean fclean re
