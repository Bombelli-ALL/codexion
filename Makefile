NAME        = codexion
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -pthread

# Include paths for all your module directories
INCLUDES    = -Iinclude \
              -Isrc/parser \
              -Isrc/printer \
              -Isrc/utils \
              -Isrc/utils/heap \
              -Isrc/monitor \
              -Isrc/dongle \
              -Isrc/coder \
              -Isrc/init

# All source files in the project
SRCS        = main.c \
              src/parser/parser.c \
              src/printer/ft_error.c \
              src/printer/ft_printer.c \
              src/utils/ft_isdigit.c \
              src/utils/ft_strlen.c \
              src/utils/ft_usleep.c \
              src/utils/is_space.c \
              src/utils/heap/heap.c \
              src/utils/heap/heap_pop_push.c \
              src/monitor/monitor.c \
              src/monitor/scheduler_utils.c \
              src/init/init.c \
              src/init/free_system.c \
              src/init/get_set_system.c \
              src/init/thread_creater.c \
              src/dongle/dongle.c \
              src/coder/coder.c

# Object files configuration
OBJ_DIR     = obj
OBJS        = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))

# Default target
all: $(NAME)

# Link the executable
$(NAME): $(OBJS)
	$(CC) -g $(CFLAGS) $(OBJS) -o $(NAME)

# Compile .c files into .o files safely, creating subdirectories dynamically
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -g $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean object files
clean:
	rm -rf $(OBJ_DIR)

# Clean objects and executable
fclean: clean
	rm -f $(NAME)

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re