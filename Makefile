NAME = push_swap

CC = cc

CFLAGS = -Wall -Wextra -Werror -I include/
CHECKER = ./checker_Mac

SRC_DIR = src
OBJ_DIR = obj

SRCS = \
	${SRC_DIR}/main.c \
	${SRC_DIR}/parser/split.c \
	${SRC_DIR}/parser/parse.c \
	${SRC_DIR}/parser/atol.c \
	${SRC_DIR}/parser/flags.c \
	${SRC_DIR}/utils/stack.c \
	${SRC_DIR}/utils/first_func.c \
	${SRC_DIR}/utils/second_func.c \
	${SRC_DIR}/utils/checks.c \
	${SRC_DIR}/utils/parse_helpers.c \
	${SRC_DIR}/utils/bench.c \
	${SRC_DIR}/ops/push_op.c \
	${SRC_DIR}/ops/reverse_rotate_op.c \
	${SRC_DIR}/ops/rotate_op.c \
	${SRC_DIR}/ops/swap_op.c \
	${SRC_DIR}/algorithms/disorder.c \
	${SRC_DIR}/algorithms/selector.c \
	${SRC_DIR}/algorithms/simple.c \
	${SRC_DIR}/algorithms/medium.c \
	${SRC_DIR}/algorithms/medium_helper.c \
	${SRC_DIR}/algorithms/complex.c \
	${SRC_DIR}/algorithms/complex_helper.c \
	${SRC_DIR}/algorithms/adaptive.c

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

BRANCH_DEV_A := alex
BRANCH_MAIN := main

a-check:
	@test "$$(git branch --show-current)" = "$(BRANCH_DEV_A)" || \
	(echo "Yanlis branch'tesin"; exit 1)

astat:
	@git branch --show-current
	@git status --short

a-pull:
	git checkout $(BRANCH_MAIN)
	git pull origin $(BRANCH_MAIN)
	git checkout $(BRANCH_DEV_A)
	git merge $(BRANCH_MAIN)

a-push: a-check
	@AI_COMMIT_ONLY_BRANCH=$(BRANCH_DEV_A) ./scripts/ai-commit.sh

a-push-m: a-check
	@read -p "Type (feat/fix/refactor/chore/docs/test): " type; \
	read -p "Scope (opsiyonel): " scope; \
	read -p "Mesaj: " subject; \
	msg=$$type; \
	if [ -n "$$scope" ]; then msg="$$msg($$scope)"; fi; \
	msg="$$msg: $$subject"; \
	git add . && \
	if ! git diff --cached --quiet; then \
		git commit -m "$$msg" && git push origin $(BRANCH_DEV_A); \
	else \
		echo "Staged degisiklik yok."; \
	fi

a-main:
	git checkout $(BRANCH_MAIN)
	git pull origin $(BRANCH_MAIN)
	git merge $(BRANCH_DEV_A)
	git push origin $(BRANCH_MAIN)
	git checkout $(BRANCH_DEV_A)

a-pushall: a-push a-main

# ─── Git Workflow Meltem ──────────────────────────────────

BRANCH_DEV_M := meltem

m-check:
	@test "$$(git branch --show-current)" = "$(BRANCH_DEV_M)" || \
	(echo "Yanlis branch'tesin"; exit 1)

mstat:
	@git branch --show-current
	@git status --short

mg:
	git checkout $(BRANCH_MAIN)
	git pull origin $(BRANCH_MAIN)
	git checkout $(BRANCH_DEV_M)
	git merge $(BRANCH_MAIN)

mp: m-check
	@AI_COMMIT_ONLY_BRANCH=$(BRANCH_DEV_M) ./scripts/ai-commit.sh

mp-m: m-check
	@read -p "Type (feat/fix/refactor/chore/docs/test): " type; \
	read -p "Scope (opsiyonel): " scope; \
	read -p "Mesaj: " subject; \
	msg=$$type; \
	if [ -n "$$scope" ]; then msg="$$msg($$scope)"; fi; \
	msg="$$msg: $$subject"; \
	git add . && \
	if ! git diff --cached --quiet; then \
		git commit -m "$$msg" && git push origin $(BRANCH_DEV_M); \
	else \
		echo "Staged degisiklik yok."; \
	fi

mm:
	git checkout $(BRANCH_MAIN)
	git pull origin $(BRANCH_MAIN)
	git merge $(BRANCH_DEV_M)
	git push origin $(BRANCH_MAIN)
	git checkout $(BRANCH_DEV_M)

ma: mp mm

# ─── Testers ──────────────────────────────────────────────────────────────────

TESTER = ./test.sh
TEST_SIZE ?= 100
TEST_COUNT ?= 10
DISORDER ?= 0.5

tester-setup:
	@chmod +x $(TESTER)
	@if [ -f ./checker_Mac ] && [ ! -f ./checker_linux ]; then \
		cp ./checker_Mac ./checker_linux; \
	fi
	@if [ -f ./checker_linux ]; then chmod +x ./checker_linux; fi

test-help: tester-setup
	@$(TESTER) --help

test: re tester-setup
	@$(TESTER)

test-custom: re tester-setup
	@$(TESTER) $(TEST_SIZE) $(TEST_COUNT)

test-extra: re tester-setup
	@$(TESTER) -extra $(TEST_SIZE) $(TEST_COUNT)

test-simple: re tester-setup
	@$(TESTER) -simple $(TEST_SIZE) $(TEST_COUNT)

test-medium: re tester-setup
	@$(TESTER) -medium $(TEST_SIZE) $(TEST_COUNT)

test-complex: re tester-setup
	@$(TESTER) -complex $(TEST_SIZE) $(TEST_COUNT)

test-disorder: re tester-setup
	@$(TESTER) -d $(DISORDER) $(TEST_SIZE) $(TEST_COUNT)

check: all
	@chmod +x $(CHECKER)
	@./$(NAME) $(ARGS) | $(CHECKER) $(ARGS)


.PHONY: all clean fclean re \
	a-pull a-push a-main a-pushall a-push-m \
	m-check mstat mg mp mm ma mp-m \
	tester-setup test-help test test-custom test-extra test-simple test-medium test-complex test-disorder check
