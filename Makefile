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
	${SRC_DIR}/bench/flags.c \
	${SRC_DIR}/stack/stack.c \
	${SRC_DIR}/utils/oldfuncs.c \
	${SRC_DIR}/utils/newfuncs.c \
	${SRC_DIR}/utils/checks.c

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
	git add . && \
	git commit -m "$$msg" && \
	git push origin alex

a-main:
	git checkout main
	git pull origin main
	git merge alex
	git push origin main
	git checkout alex

a-pushall: a-push a-main


# ─── Git Workflow Meltem ──────────────────────────────────

BRANCH_DEV := meltem
BRANCH_MAIN := main

m-check:
	@test "$$(git branch --show-current)" = "$(BRANCH_DEV)" || \
	(echo "Yanlis branch'tesin"; exit 1)

mstat:
	@git branch --show-current
	@git status --short

mg:
	git checkout $(BRANCH_MAIN)
	git pull origin $(BRANCH_MAIN)
	git checkout $(BRANCH_DEV)
	git merge $(BRANCH_MAIN)

mp: m-check
	@AI_COMMIT_ONLY_BRANCH=$(BRANCH_DEV) $(HOME)/.local/bin/ai-commit

mp-m: m-check
	@read -p "Type (feat/fix/refactor/chore/docs/test): " type; \
	read -p "Scope (opsiyonel): " scope; \
	read -p "Mesaj: " subject; \
	msg=$$type; \
	if [ -n "$$scope" ]; then msg="$$msg($$scope)"; fi; \
	msg="$$msg: $$subject"; \
	git add . && \
	if ! git diff --cached --quiet; then \
		git commit -m "$$msg" && git push origin $(BRANCH_DEV); \
	else \
		echo "Staged degisiklik yok."; \
	fi

mm:
	git checkout $(BRANCH_MAIN)
	git pull origin $(BRANCH_MAIN)
	git merge $(BRANCH_DEV)
	git push origin $(BRANCH_MAIN)
	git checkout $(BRANCH_DEV)

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

.PHONY: all clean fclean re \
	a-pull a-push a-main a-pushall \
	m-check mstat mg mp mm ma mp-m \
	test test-extended test-combo test-combo-deep test-all
