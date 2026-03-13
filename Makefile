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

sabah-a:
	git checkout main
	git pull origin main
	git checkout alex
	git merge main

push-a:
	@read -p "Commit mesaji: " msg; \
	git add .; \
	git commit -m "$$msg"; \
	git push origin alex

main-a:
	git checkout main
	git pull origin main
	git merge alex
	git push origin main
	git checkout alex


# ─── Git Workflow Meltem ────────────────────────────────────────────────────────────

sabah-m:
	git checkout main
	git pull origin main
	git checkout meltem
	git merge main

push-m:
	@read -p "Commit mesaji: " msg; \
	git add .; \
	git commit -m "$$msg"; \
	git push origin meltem

main-m:
	git checkout main
	git pull origin main
	git merge meltem
	git push origin main
	git checkout meltem


.PHONY: all fclean clean re sabah-a push-a main-a sabah-m push-m main-m
