NAME        = codexion
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -pthread

INCLUDES    = -Iinclude \
              -Isrc/parser \
              -Isrc/printer \
              -Isrc/utils \
              -Isrc/utils/heap \
              -Isrc/monitor \
              -Isrc/dongle \
              -Isrc/coder \
              -Isrc/init


SRCS        = main.c \
              src/parser/parser.c \
              src/printer/ft_error.c \
              src/printer/ft_printer.c \
              src/utils/ft_isdigit.c \
              src/utils/ft_strlen.c \
              src/utils/ft_usleep.c \
              src/utils/is_space.c \
              src/utils/heap/heap.c \
              src/utils/heap/heap_utils.c \
              src/monitor/monitor.c \
              src/monitor/scheduler_utils.c \
              src/init/init.c \
              src/init/free_system.c \
              src/init/get_set_system.c \
              src/init/thread_creater.c \
              src/dongle/dongle.c \
              src/coder/coder.c \
              src/coder/coder_get_set.c


OBJ_DIR     = obj
OBJS        = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))


all: $(NAME)


$(NAME): $(OBJS)
	$(CC) -g $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -g $(CFLAGS) $(INCLUDES) -c $< -o $@


clean:
	rm -rf $(OBJ_DIR)


fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re