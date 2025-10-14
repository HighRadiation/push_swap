#------------------------------------------
# General Settings
# -----------------------------------------
NAME = push_swap
CC = cc
CFLAGS = -Wall -Wextra -Werror -I include

# Source Files, all folders are included
SRC = $(shell find src -name "*.c")
OBJ = $(SRC:.c=.o)

# -----------------------------------------
# Rules
# -----------------------------------------

all: $(NAME)

# Make program
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Cleaning
clean:
	rm -f $(OBJ)
# Full cleaning
fclean:
	rm -f $(NAME)

# Full clean & Make program
re: fclean all

# Goals
.PHONY: all clean fclean re
