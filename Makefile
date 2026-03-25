NAME = push_swap

CC = cc

CFLAGS = -Wall -Wextra -Werror -I include/

SRC_DIR = src
OBJ_DIR = obj

SRCS = \
	${SRC_DIR}/main.c \
	${SRC_DIR}/parser/split.c \
	${SRC_DIR}/parser/parse.c \
	${SRC_DIR}/parser/atol.c \
	${SRC_DIR}/parser/flags.c \
	${SRC_DIR}/utils/stack.c \
	${SRC_DIR}/utils/oldfuncs.c \
	${SRC_DIR}/utils/newfuncs.c \
	${SRC_DIR}/utils/checks.c \
	${SRC_DIR}/utils/parse_helpers.c \
	${SRC_DIR}/ops/push_op.c \
	${SRC_DIR}/ops/reverse_rotate_op.c \
	${SRC_DIR}/ops/rotate_op.c \
	${SRC_DIR}/ops/swap_op.c \
	${SRC_DIR}/algorithms/disorder.c \
	${SRC_DIR}/algorithms/selector.c \
	${SRC_DIR}/algorithms/simple/simple.c \
	${SRC_DIR}/algorithms/medium/medium.c \
	${SRC_DIR}/algorithms/complex/complex.c \
	${SRC_DIR}/algorithms/adaptive/adaptive.c

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

TESTER_DIR := testers

test:  re
	@chmod +x $(TESTER_DIR)/parse_tester.sh
	@$(TESTER_DIR)/parse_tester.sh --skip-build

test-combo: re
	@chmod +x $(TESTER_DIR)/parse_combo_tester.sh
	@$(TESTER_DIR)/parse_combo_tester.sh --skip-build

test-combo-deep: re
	@chmod +x $(TESTER_DIR)/parse_combo_tester.sh
	@$(TESTER_DIR)/parse_combo_tester.sh --skip-build --max-args 1 --max-flags 1

test-extended: re
	@chmod +x $(TESTER_DIR)/parse_tester_extended.sh
	@$(TESTER_DIR)/parse_tester_extended.sh --skip-build

test-all: re
	@chmod +x $(TESTER_DIR)/parse_tester.sh \
	          $(TESTER_DIR)/parse_tester_extended.sh \
	          $(TESTER_DIR)/parse_combo_tester.sh
	@$(TESTER_DIR)/parse_tester.sh --skip-build
	@$(TESTER_DIR)/parse_tester_extended.sh --skip-build
	@$(TESTER_DIR)/parse_combo_tester.sh --skip-build

check: all
	@chmod +x $(CHECKER)
	@./$(NAME) $(ARGS) | $(CHECKER) $(ARGS)

.PHONY: all clean fclean re \
	a-pull a-push a-main a-pushall a-push-m \
	m-check mstat mg mp mm ma mp-m \
	test test-extended test-combo test-combo-deep test-all check
