NAME = push_swap

CC = cc

CFLAGS = -Wall -Wextra -Werror -I include/

SRC_DIR = src
OBJ_DIR = obj

SRCS = \
	${SRC_DIR}/main.c \
	${SRC_DIR}/parser/split.c \
	${SRC_DIR}/parser/atol.c\
	${SRC_DIR}/parser/ft_libft.c\

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: ${NAME}

${NAME} : ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf ${OBJ_DIR}

fclean: clean
	rm -rf ${NAME}

re: fclean all

# ─── Git Workflow Alex ────────────────────────────────────────────────────────────

a-pull:
	git checkout main
	git pull origin main
	git checkout alex
	git merge main

a-push:
	@read -p "Commit mesaji: " msg; \
	git add .; \
	git commit -m "$$msg"; \
	git push origin alex

a-main:
	git checkout main
	git pull origin main
	git merge alex
	git push origin main
	git checkout alex

a-pushall: a-push a-main


# ─── Git Workflow Meltem ────────────────────────────────────────────────────────────

m-pull:
	git checkout main
	git pull origin main
	git checkout meltem
	git merge main

m-push:
	@read -p "Commit mesaji: " msg; \
	git add .; \
	git commit -m "$$msg"; \
	git push origin meltem

m-main:
	git checkout main
	git pull origin main
	git merge meltem
	git push origin main
	git checkout meltem

m-pushall: m-push m-main

.PHONY: all fclean clean re a-pull m-pull a-push m-push a-main m-main a-pushall m-pushall
