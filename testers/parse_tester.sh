#!/usr/bin/env bash

set -u

PASS=0
FAIL=0
TOTAL=0
VERBOSE=0
SKIP_BUILD=0
BIN="./push_swap"
START_TS=$(date +%s)

usage() {
	echo "Usage: $0 [--verbose|-v] [--skip-build] [--bin PATH]"
}

test_ok() {
	run_expect_ok "$@"
}

test_err() {
	run_expect_err "$@"
}

test_ok_silent() {
	run_expect_ok_silent "$@"
}

print_output() {
	if [ -s "$1" ]; then
		echo "  output:"
		sed 's/^/    /' "$1"
	fi
}

run_expect_ok() {
	local name="$1"
	local out_file
	local status
	shift
	TOTAL=$((TOTAL + 1))
	out_file=$(mktemp)
	"$@" >"$out_file" 2>&1
	status=$?
	if [ "$status" -eq 0 ]; then
		echo "[PASS] $name"
		PASS=$((PASS + 1))
	else
		echo "[FAIL] $name (expected success, got exit=$status)"
		print_output "$out_file"
		FAIL=$((FAIL + 1))
	fi
	if [ "$VERBOSE" -eq 1 ] && [ "$status" -eq 0 ]; then
		print_output "$out_file"
	fi
	rm -f "$out_file"
}

run_expect_err() {
	local name="$1"
	local out_file
	local status
	shift
	TOTAL=$((TOTAL + 1))
	out_file=$(mktemp)
	"$@" >"$out_file" 2>&1
	status=$?
	if [ "$status" -eq 0 ]; then
		echo "[FAIL] $name (expected error, got success)"
		print_output "$out_file"
		FAIL=$((FAIL + 1))
	elif grep -q "Error" "$out_file"; then
		echo "[PASS] $name"
		PASS=$((PASS + 1))
	else
		echo "[FAIL] $name (non-zero exit without \"Error\" output)"
		print_output "$out_file"
		FAIL=$((FAIL + 1))
	fi
	if [ "$VERBOSE" -eq 1 ] && [ "$status" -ne 0 ]; then
		print_output "$out_file"
	fi
	rm -f "$out_file"
}

run_expect_ok_silent() {
	local name="$1"
	local out_file
	local status
	shift
	TOTAL=$((TOTAL + 1))
	out_file=$(mktemp)
	"$@" >"$out_file" 2>&1
	status=$?
	if [ "$status" -ne 0 ]; then
		echo "[FAIL] $name (expected success, got exit=$status)"
		print_output "$out_file"
		FAIL=$((FAIL + 1))
	elif [ -s "$out_file" ]; then
		echo "[FAIL] $name (expected no output)"
		print_output "$out_file"
		FAIL=$((FAIL + 1))
	else
		echo "[PASS] $name"
		PASS=$((PASS + 1))
	fi
	rm -f "$out_file"
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
				usage
				exit 2
			fi
			BIN="$1"
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

run_default_tests() {
	test_ok "valid multi args" "$BIN" 3 2 1
	test_ok "valid single string" "$BIN" "3 2 1"
	test_ok "only flag no numbers" "$BIN" --bench
	test_err "invalid token" "$BIN" 1 a 3
	test_err "duplicate values" "$BIN" 1 2 2
	test_err "overflow positive" "$BIN" 2147483648
	test_err "overflow negative" "$BIN" -2147483649
	test_ok "signed values" "$BIN" +42 -7 0
	test_ok "whitespace split" "$BIN" "   10   -2   5   "
	test_ok "flag plus numbers" "$BIN" --adaptive 4 1 3 2
}

run_error_edge_tests() {
	test_err "nonnumeric alpha" "$BIN" 1 abc 3
	test_err "nonnumeric float" "$BIN" 1 2.5 3
	test_err "nonnumeric special char" "$BIN" 1 @ 3
	test_err "empty string arg" "$BIN" "" 1
	test_err "whitespace only arg" "$BIN" " " 1
	test_err "expression token" "$BIN" 1 2+3
	test_err "unknown flag token" "$BIN" 1 --foo 2

	test_err "overflow int max plus one" "$BIN" 2147483648
	test_err "overflow int min minus one" "$BIN" -2147483649
	test_err "overflow very large" "$BIN" 99999999999
	test_ok "boundary int max" "$BIN" 2147483647
	test_ok "boundary int min" "$BIN" -2147483648

	test_err "duplicate middle" "$BIN" 1 2 2 3
	test_err "duplicate zeros" "$BIN" 0 0
	test_err "duplicate negative" "$BIN" -1 2 -1
	test_err "duplicate minus zero zero" "$BIN" -0 0
}

run_valid_silent_tests() {
	test_ok_silent "no args" "$BIN"
	test_ok_silent "only adaptive flag" "$BIN" --adaptive
	test_ok_silent "only bench flag" "$BIN" --bench
	test_ok_silent "single value" "$BIN" 42
	test_ok_silent "single value int min" "$BIN" -2147483648
	test_ok_silent "already sorted ascending" "$BIN" 1 2 3 4 5
	test_ok_silent "already sorted mixed" "$BIN" -3 -2 -1 0 1
	test_ok_silent "single minus zero" "$BIN" -0
}

run_ambiguous_policy_tests() {
	# Project policy (current behavior):
	test_ok "leading zero accepted" "$BIN" 01 2 3
	test_ok "plus sign accepted" "$BIN" +1 2 3
	test_ok "quoted one arg split" "$BIN" "1 2 3"
	test_err "multiple quoted groups rejected" "$BIN" "1 2" "3 4"
	test_err "flag in middle rejected" "$BIN" 1 2 --simple 3
}

run_sign_and_format_edge_tests() {
	test_err "single plus sign" "$BIN" +
	test_err "single minus sign" "$BIN" -
	test_err "double plus sign" "$BIN" ++1 2
	test_err "double minus sign" "$BIN" --1 2
	test_err "mixed sign token" "$BIN" +-1 2
	test_err "sign with spaces token" "$BIN" " + " 1
	test_err "duplicate plus zero and zero" "$BIN" +0 0
	test_err "duplicate +1 and 1" "$BIN" +1 1
}

run_quoted_argument_tests() {
	test_ok "quoted tabs and newlines split" "$BIN" $'1\t2\n3'
	test_ok "quoted with leading trailing spaces" "$BIN" "   1 2 3   "
	test_err "quoted empty with second token" "$BIN" "" "2"
	test_err "quoted spaced pairs rejected" "$BIN" " 1" "2 "
}

run_flag_combo_tests() {
	test_ok "bench with complex" "$BIN" --bench --complex 5 4 3
	test_ok "bench with adaptive" "$BIN" --bench --adaptive 5 1 4 2 3
	test_ok "bench with simple" "$BIN" --bench --simple 2 1
	test_ok_silent "simple without numbers" "$BIN" --simple
	test_ok_silent "complex without numbers" "$BIN" --complex
	test_err "two algo flags conflict" "$BIN" --simple --medium 1 2 3
	test_err "three algo flags conflict" "$BIN" --adaptive --complex --simple 1 2
	test_err "unknown flag at start" "$BIN" --foo 1 2
}

run_valid_order_tests() {
	test_ok "two values unsorted" "$BIN" 2 1
	test_ok "three values reverse" "$BIN" 3 2 1
	test_ok "neg zero pos mixed" "$BIN" 0 -1 1
	test_ok "int min and max pair" "$BIN" -2147483648 2147483647
}

run_format_corner_tests() {
	test_err "hex style 0x1" "$BIN" 0x1 2 3
	test_err "binary style 0b101" "$BIN" 0b101 2 3
	test_err "scientific 1e5" "$BIN" 1e5 2 3
	test_err "underscore 1_000" "$BIN" 1_000 2 3
	test_err "trailing alpha 1a" "$BIN" 1a 2 3
	test_err "bare plus sign" "$BIN" + 2 3
	test_err "bare minus sign" "$BIN" - 2 3
	test_ok  "multi leading zero 007" "$BIN" 007 2 3
	test_ok  "double zero" "$BIN" 00 2 3
	test_ok  "near int max" "$BIN" 2147483646 1
	test_ok  "near int min" "$BIN" -2147483647 1
	test_err "very negative overflow" "$BIN" -99999999999
}

run_whitespace_arg_tests() {
	test_ok  "trailing space single-arg (split path)" "$BIN" "1 "
	test_ok  "leading space single-arg (split path)" "$BIN" " 1"
	test_err "double space only" "$BIN" "  "
	test_err "newline only arg" "$BIN" $'\n'
	test_err "double tab arg" "$BIN" $'\t\t'
	test_err "trailing space multi-arg" "$BIN" "1 " "2"
	test_err "leading space multi-arg" "$BIN" " 1" "2"
}

run_large_sequence_tests() {
	test_ok_silent "5 sorted negatives" "$BIN" -5 -4 -3 -2 -1
	test_ok "5 unsorted negatives" "$BIN" -1 -3 -2 -5 -4
	test_ok_silent "10 sorted elements" "$BIN" 1 2 3 4 5 6 7 8 9 10
	test_ok "10 unsorted elements" "$BIN" 10 1 9 2 8 3 7 4 6 5
	test_ok "near boundary pair min" "$BIN" -2147483648 -2147483647
	test_ok "near boundary pair max" "$BIN" 2147483646 2147483647
	test_err "large sequence with duplicate" "$BIN" 1 2 3 4 5 1
	test_err "all same value" "$BIN" 3 3 3
}

run_user_tests() {
	test_ok "valid mixed values" "$BIN" 8 3 -1 0
	test_err "invalid token letter" "$BIN" 4 z 2
	test_ok "5 +05" "$BIN" 6 +05
	test_err "5+5" "$BIN" 5+5 "3"
	test_err "5 - 5" "$BIN" 5 - 5 "3"
	test_err "5 + 5" "$BIN" 5 + 5 "3"
	test_err "5 -5-5" "$BIN" 5 -5-5 "3"
	test_err "5 +5+5" "$BIN" 5 +5+5 "3"
	test_err "5 -5 +5" "$BIN" 5 -5 +5+ "3"
	test_err "5 -5 +5" "$BIN" -5 5+ "3"
	test_err "5 -5 +5" "$BIN" 5 -5+ "3"
	test_err "5 -5 +5" "$BIN" 5 -5- "3"

}

run_default_tests
run_error_edge_tests
run_valid_silent_tests
run_ambiguous_policy_tests
run_sign_and_format_edge_tests
run_quoted_argument_tests
run_flag_combo_tests
run_valid_order_tests
run_format_corner_tests
run_whitespace_arg_tests
run_large_sequence_tests
run_user_tests

ELAPSED=$(( $(date +%s) - START_TS ))

echo ""
echo "Summary: TOTAL=$TOTAL PASS=$PASS FAIL=$FAIL TIME=${ELAPSED}s"

if [ "$FAIL" -ne 0 ]; then
	exit 1
fi

exit 0
