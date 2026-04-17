NAME = push_swap

CC = cc

CFLAGS = -Wall -Wextra -Werror
OBJ_DIR = obj

SRCS = \
	01_main.c \
	02_03_split.c \
	02_03_parse.c \
	02_03_atol.c \
	02_03_flags.c \
	02_03_parse_helpers.c \
	02_03_argv_build.c \
	02_03_validate.c \
	02_04_stack.c \
	02_04_first_func.c \
	02_04_second_func.c \
	02_04_ft_printf_fd.c \
	02_04_checks.c \
	02_04_bench.c \
	02_02_push_op.c \
	02_02_reverse_rotate_op.c \
	02_02_rotate_op.c \
	02_02_swap_op.c \
	02_01_disorder.c \
	02_01_selector.c \
	02_01_simple.c \
	02_01_medium.c \
	02_01_medium_helper.c \
	02_01_complex.c \
	02_01_complex_helper.c \
	02_01_five_or_less.c \
	02_01_five_or_less_helper.c \
	02_01_adaptive.c

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all: ${NAME}

${NAME} : ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf ${OBJ_DIR}

fclean: clean
	rm -rf ${NAME}

re: fclean all

.PHONY: all clean fclean re
