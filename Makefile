NAME = push_swap
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Source files
SRCS = main.c \
       stack_init.c \
       operations/ops_swap.c \
       operations/ops_push.c \
       operations/ops_rotate.c \
       operations/ops_rev_rotate.c \
       sort.c \
       radix_sort.c \
       utils/utils.c \
       utils/utils_extra.c \
       utils/utils_parse.c

# Object files
OBJS = $(SRCS:.c=.o)

# Libft
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

# Rules
all: $(NAME)


BLUE = \033[0;34m
GREEN = \033[0;32m
YELLOW = \033[1;33m
RESET = \033[0m

$(NAME): $(OBJS) $(LIBFT)
	@echo "$(BLUE)Linking...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)Build complete!$(RESET)"

%.o: %.c
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -I. -c $< -o $@

$(LIBFT):
	@echo "$(BLUE)Building libft...$(RESET)"
	@$(MAKE) -s -C $(LIBFT_DIR)

clean:
	@echo "$(BLUE)Cleaning object files...$(RESET)"
	@rm -f $(OBJS)
	@$(MAKE) -s -C $(LIBFT_DIR) clean

fclean: clean
	@echo "$(BLUE)Removing executable...$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean

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
