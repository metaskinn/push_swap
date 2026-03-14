#!/usr/bin/env bash

set -u

BIN="./push_swap"
SKIP_BUILD=0
VERBOSE=0
MAX_ARGS=2
MAX_FLAGS=1
PROGRESS_EVERY=500

TOTAL=0
PASS=0
FAIL=0
FAIL_CRASH=0
FAIL_BAD_ERROR=0
FAIL_ERROR_ON_SUCCESS=0

START_TS=$(date +%s)

# Parse-domain token pool. Deliberately mixed: valid, edge, and invalid.
# Each extra token multiplies the combination count — tune max-args accordingly.
# Quick run:   --max-args 2 --max-flags 1  (~3 K combos)
# Deep run:    --max-args 3 --max-flags 2  (~700 K combos, slow in bash)
TOKENS=(
	# boundary values
	"2147483647"
	"-2147483647"
	"2147483648"
	"-2147483648"
	"461168601413242060"
	"-461168601413242060"
	"4611686014132420609"
	"-4611686014132420609"
	"46116860141324206093"
	"-46116860141324206093"
	"46116860141324206093461168601413242060934611686014132420609346116860141324206093461168601413242060934611686014132420609346116860141324206093461168601413242060934"
	"-46116860141324206093461168601413242060934611686014132420609346116860141324206093461168601413242060934611686014132420609346116860141324206093461168601413242060934"
	# normal valid
	"-1"
	"0"
	"1"
	"2"
	# sign variants
	"+1"
	"-0"
	"+"
	"-"
	# leading-zero variants (accepted by parser as int value)
	"01"
	"007"
	# invalid format tokens
	"0x1"
	"1e5"
	"abc"
	"2.5"
	"@"
	"1a"
	# whitespace / empty
	""
	" "
	"2+3"
	"4-5"
	"6 + 7"
	"8 - 9"
	"+ "
	"- "
	" 			"
)

# Includes known flags and one unknown flag to exercise parser robustness.
FLAGS=(
	"--bench"
	"--simple"
	"--medium"
	"--complex"
	"--adaptive"
	"--foo"
)

usage() {
	echo "Usage: $0 [--bin PATH] [--skip-build] [--verbose|-v] [--max-args N] [--max-flags N] [--progress-every N]"
}

is_uint() {
	case "$1" in
		""|*[!0-9]*) return 1 ;;
		*) return 0 ;;
	esac
}

print_case() {
	local prefix="$1"
	shift
	echo "$prefix$*"
}

run_case() {
	local out_file
	local status
	local cmd_display
	local has_error=0

	TOTAL=$((TOTAL + 1))
	out_file=$(mktemp)

	cmd_display="$BIN"
	for arg in "$@"; do
		cmd_display="$cmd_display [${arg}]"
	done

	"$BIN" "$@" >"$out_file" 2>&1
	status=$?

	if grep -q "Error" "$out_file"; then
		has_error=1
	fi

	if [ "$status" -eq 0 ] && [ "$has_error" -eq 0 ]; then
		PASS=$((PASS + 1))
	elif [ "$status" -ge 128 ]; then
		FAIL=$((FAIL + 1))
		FAIL_CRASH=$((FAIL_CRASH + 1))
		echo "[CRASH] exit=$status :: $cmd_display"
		if [ -s "$out_file" ]; then
			sed 's/^/    /' "$out_file"
		fi
	elif [ "$status" -ne 0 ] && [ "$has_error" -eq 0 ]; then
		FAIL=$((FAIL + 1))
		FAIL_BAD_ERROR=$((FAIL_BAD_ERROR + 1))
		echo "[FAIL] non-zero without Error (exit=$status) :: $cmd_display"
		if [ -s "$out_file" ]; then
			sed 's/^/    /' "$out_file"
		fi
	elif [ "$status" -eq 0 ] && [ "$has_error" -eq 1 ]; then
		FAIL=$((FAIL + 1))
		FAIL_ERROR_ON_SUCCESS=$((FAIL_ERROR_ON_SUCCESS + 1))
		echo "[FAIL] success with Error output :: $cmd_display"
		if [ -s "$out_file" ]; then
			sed 's/^/    /' "$out_file"
		fi
	else
		PASS=$((PASS + 1))
	fi

	if [ "$VERBOSE" -eq 1 ]; then
		if [ -s "$out_file" ]; then
			print_case "[CASE] " "$cmd_display"
			sed 's/^/    /' "$out_file"
		fi
	fi

	rm -f "$out_file"

	if [ "$PROGRESS_EVERY" -gt 0 ] && [ $((TOTAL % PROGRESS_EVERY)) -eq 0 ]; then
		echo "[INFO] progress TOTAL=$TOTAL PASS=$PASS FAIL=$FAIL"
	fi
}

CURRENT_ARGS=()
CURRENT_FLAGS=()

run_with_current_flags() {
	local cmd=()
	local i

	for i in ${CURRENT_FLAGS[@]+"${CURRENT_FLAGS[@]}"}; do
		cmd+=("$i")
	done
	for i in ${CURRENT_ARGS[@]+"${CURRENT_ARGS[@]}"}; do
		cmd+=("$i")
	done
	if [ "${#cmd[@]}" -eq 0 ]; then
		run_case
	else
		run_case "${cmd[@]}"
	fi
}

enum_flag_combos() {
	local depth="$1"
	local target="$2"
	local f

	if [ "$depth" -eq "$target" ]; then
		run_with_current_flags
		return
	fi
	for f in "${FLAGS[@]}"; do
		CURRENT_FLAGS[$depth]="$f"
		enum_flag_combos $((depth + 1)) "$target"
	done
}

enum_arg_combos() {
	local depth="$1"
	local target="$2"
	local t

	if [ "$depth" -eq "$target" ]; then
		local fl
		CURRENT_FLAGS=()
		for fl in $(seq 0 "$MAX_FLAGS"); do
			enum_flag_combos 0 "$fl"
		done
		return
	fi
	for t in "${TOKENS[@]}"; do
		CURRENT_ARGS[$depth]="$t"
		enum_arg_combos $((depth + 1)) "$target"
	done
}

while [ "$#" -gt 0 ]; do
	case "$1" in
		-v|--verbose)
			VERBOSE=1
			;;
		--skip-build)
			SKIP_BUILD=1
			;;
		--bin)
			shift
			if [ "$#" -eq 0 ]; then
				echo "Missing value for --bin"
				exit 2
			fi
			BIN="$1"
			;;
		--max-args)
			shift
			if [ "$#" -eq 0 ] || ! is_uint "$1"; then
				echo "Invalid value for --max-args"
				exit 2
			fi
			MAX_ARGS="$1"
			;;
		--max-flags)
			shift
			if [ "$#" -eq 0 ] || ! is_uint "$1"; then
				echo "Invalid value for --max-flags"
				exit 2
			fi
			MAX_FLAGS="$1"
			;;
		--progress-every)
			shift
			if [ "$#" -eq 0 ] || ! is_uint "$1"; then
				echo "Invalid value for --progress-every"
				exit 2
			fi
			PROGRESS_EVERY="$1"
			;;
		-h|--help)
			usage
			exit 0
			;;
		*)
			echo "Unknown option: $1"
			usage
			exit 2
			;;
	esac
	shift
done

if [ "$SKIP_BUILD" -eq 0 ]; then
	if ! make -s; then
		echo "Build failed"
		exit 1
	fi
fi

if [ ! -x "$BIN" ]; then
	echo "Binary not executable: $BIN"
	exit 1
fi

echo "[INFO] starting combo test: max_args=$MAX_ARGS max_flags=$MAX_FLAGS tokens=${#TOKENS[@]} flags=${#FLAGS[@]}"

for arg_len in $(seq 0 "$MAX_ARGS"); do
	CURRENT_ARGS=()
	enum_arg_combos 0 "$arg_len"
done

ELAPSED=$(( $(date +%s) - START_TS ))

echo ""
echo "Summary: TOTAL=$TOTAL PASS=$PASS FAIL=$FAIL CRASH=$FAIL_CRASH BAD_ERROR=$FAIL_BAD_ERROR ERROR_ON_SUCCESS=$FAIL_ERROR_ON_SUCCESS TIME=${ELAPSED}s"

if [ "$FAIL" -ne 0 ]; then
	exit 1
fi

exit 0
