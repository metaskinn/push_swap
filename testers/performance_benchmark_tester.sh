#!/usr/bin/env bash

set -u

BIN="./push_swap"
CHECKER_BIN="./checker_Mac"
SKIP_BUILD=0
RUNS_100=5
RUNS_500=5
QUIET=0

MIN_100=2000
GOOD_100=1500
EXCELLENT_100=700

MIN_500=12000
GOOD_500=8000
EXCELLENT_500=5500

usage() {
	echo "Usage: $0 [--bin PATH] [--checker PATH] [--skip-build] [--runs-100 N] [--runs-500 N] [--quiet]"
}

is_uint() {
	case "$1" in
		""|*[!0-9]*) return 1 ;;
		*) return 0 ;;
	esac
}

generate_unique_numbers() {
	# Generate N unique random ints in signed 32-bit range.
	local n="$1"
	local tmp
	local tmp2
	local current
	local need

	tmp=$(mktemp)
	tmp2=$(mktemp)
	: > "$tmp"

	while :; do
		current=$(wc -l < "$tmp" | tr -d ' ')
		if [ "$current" -ge "$n" ]; then
			break
		fi
		need=$((n - current))
		# jot exists on macOS and is fast for random integer streams.
		jot -r "$((need * 4 + 20))" -2147483648 2147483647 > "$tmp2"
		cat "$tmp" "$tmp2" | awk '!seen[$0]++' > "$tmp2.unique"
		mv "$tmp2.unique" "$tmp"
	done

	head -n "$n" "$tmp" | paste -sd' ' -
	rm -f "$tmp" "$tmp2"
}

run_one_case() {
	local size="$1"
	local numbers
	local ops
	local check_result
	local op_count
	local -a arr

	numbers=$(generate_unique_numbers "$size")
	# shellcheck disable=SC2206
	arr=($numbers)

	ops=$("$BIN" "${arr[@]}")
	op_count=$(printf "%s\n" "$ops" | sed '/^$/d' | wc -l | tr -d ' ')

	check_result=$(printf "%s\n" "$ops" | "$CHECKER_BIN" "${arr[@]}")

	echo "$op_count|$check_result"
}

run_group() {
	local size="$1"
	local runs="$2"
	local min_limit="$3"
	local good_limit="$4"
	local excellent_limit="$5"

	local i=1
	local result
	local op_count
	local check_result
	local sum=0
	local worst=0
	local min_pass=0
	local good_pass=0
	local excellent_pass=0
	local ko_count=0

	echo ""
	echo "=== Benchmark: $size numbers ($runs runs) ==="

	while [ "$i" -le "$runs" ]; do
		result=$(run_one_case "$size")
		op_count=${result%%|*}
		check_result=${result#*|}

		if [ "$check_result" != "OK" ]; then
			ko_count=$((ko_count + 1))
		fi

		sum=$((sum + op_count))
		if [ "$op_count" -gt "$worst" ]; then
			worst="$op_count"
		fi

		if [ "$op_count" -lt "$min_limit" ]; then
			min_pass=$((min_pass + 1))
		fi
		if [ "$op_count" -lt "$good_limit" ]; then
			good_pass=$((good_pass + 1))
		fi
		if [ "$op_count" -lt "$excellent_limit" ]; then
			excellent_pass=$((excellent_pass + 1))
		fi

		if [ "$QUIET" -eq 0 ]; then
			echo "Run $i: ops=$op_count checker=$check_result"
		fi

		i=$((i + 1))
	done

	echo "Average ops: $((sum / runs))"
	echo "Worst ops:   $worst"
	echo "< $min_limit (minimum):  $min_pass/$runs"
	echo "< $good_limit (good):    $good_pass/$runs"
	echo "< $excellent_limit (excellent): $excellent_pass/$runs"
	echo "Checker KO/Error: $ko_count/$runs"

	if [ "$ko_count" -ne 0 ] || [ "$min_pass" -ne "$runs" ]; then
		return 1
	fi
	return 0
}

while [ "$#" -gt 0 ]; do
	case "$1" in
		--bin)
			shift
			if [ "$#" -eq 0 ]; then
				echo "Missing value for --bin"
				exit 2
			fi
			BIN="$1"
			;;
		--checker)
			shift
			if [ "$#" -eq 0 ]; then
				echo "Missing value for --checker"
				exit 2
			fi
			CHECKER_BIN="$1"
			;;
		--skip-build)
			SKIP_BUILD=1
			;;
		--runs-100)
			shift
			if [ "$#" -eq 0 ] || ! is_uint "$1" || [ "$1" -eq 0 ]; then
				echo "Invalid value for --runs-100"
				exit 2
			fi
			RUNS_100="$1"
			;;
		--runs-500)
			shift
			if [ "$#" -eq 0 ] || ! is_uint "$1" || [ "$1" -eq 0 ]; then
				echo "Invalid value for --runs-500"
				exit 2
			fi
			RUNS_500="$1"
			;;
		--quiet)
			QUIET=1
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

if [ ! -x "$CHECKER_BIN" ]; then
	echo "Checker not executable: $CHECKER_BIN"
	exit 1
fi

status=0

run_group 100 "$RUNS_100" "$MIN_100" "$GOOD_100" "$EXCELLENT_100" || status=1
run_group 500 "$RUNS_500" "$MIN_500" "$GOOD_500" "$EXCELLENT_500" || status=1

echo ""
if [ "$status" -eq 0 ]; then
	echo "Result: PASS (all runs satisfy minimum limits and checker output is OK)"
else
	echo "Result: FAIL (at least one run exceeded minimum limit or checker was not OK)"
fi

exit "$status"
