NAME = push_swap

CC = cc

CFLAGS = -Wall -Wextra -Werror -I include/



SRC_DIR = src
OBJ_DIR = obj



SRCS = \
	${PATH}/main.c \
	${PATH}/parser/split.c \
	${PATH}/parser/atol.c\
	${PATH}/parser/ft_libft.c
	
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: ${NAME}

${NAME} : ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
clean:
	rm -rf ${OBJ_DIR}

fclean: clean
	rm -rf ${NAME}

re: fclean all

.PHONY: all fclean clean re
