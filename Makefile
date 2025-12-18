NAME = push_swap
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Source files
SRCS = main.c \
       stack_init.c \
       ops_swap.c \
       ops_push.c \
       ops_rotate.c \
       ops_rev_rotate.c \
       sort.c \
       radix_sort.c \
       utils.c \
       utils_extra.c \
       utils_parse.c

# Object files
OBJS = $(SRCS:.c=.o)

# Libft
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

# Rules
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

test100: $(NAME)
	@ARG=$$(seq -1000 1000 | shuf -n 100 | xargs); \
	echo "count for 100 numbers:"; \
	./push_swap $$ARG | wc -l

test500: $(NAME)
	@ARG=$$(seq -1000 1000 | shuf -n 500 | xargs); \
	echo "count for 500 numbers:"; \
	./push_swap $$ARG | wc -l

.PHONY: all clean fclean re test100 test500
