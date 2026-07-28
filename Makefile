NAME        = test_parser
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -pthread

# Include paths for your module directories
INCLUDES    = -Iinclude \
              -Isrc/parser \
              -Isrc/printer \
              -Isrc/utils \
              -Isrc/int \
              -Isrc/monitor \
              -Isrc/dongle \
              -Isrc/coder

# ONLY the source files required to test parsing
SRCS        = main.c \
              src/parser/parser.c \
              src/printer/ft_error.c \
              src/utils/ft_isdigit.c \
              src/utils/ft_strlen.c \
              src/utils/is_space.c

# Object files configuration
OBJ_DIR     = obj
OBJS        = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))

# Default target
all: $(NAME)

# Link the executable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# Compile .c files into .o files
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean object files
clean:
	rm -rf $(OBJ_DIR)

# Clean objects and executable
fclean: clean
	rm -f $(NAME)

# Rebuild
re: fclean all

.PHONY: all clean fclean re