NAME = push_swap

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS = \
	src/main.c \
	src/parser/split.c \
	src/helpers/atol.c

OBJS = $(SRCS:.c=.o)

all: ${NAME}

${NAME} : ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
	rm -rf ${OBJS}

fclean: clean
	rm -rf ${NAME}

re: fclean all

.PHONY: all fclean clean re
