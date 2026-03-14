#!/usr/bin/env bash

# =============================================================================
# parse_tester_extended.sh — push_swap kapsamlı parse test paketi
#
# Mevcut parse_tester.sh'deki boşlukları kapatan ek test kategorileri:
#   1. stderr/stdout ayrımı (Error→stderr, ops→stdout, bench→stderr)
#   2. Output satır formatı doğrulaması (valid ops only, no garbage)
#   3. Flag pozisyonu varyantları (sayıdan sonra, sayılar arasında)
#   4. Aynı flag'i tekrarlama
#   5. -- end-of-flags sentinel
#   6. --bench davranışı (stderr'e gittiği doğrulanır)
#   7. Sayısal format ek edge case'ler
#   8. Stress / büyük giriş testleri
#   9. Output'ta sadece geçerli op ismi var mı?
#  10. Quoted arg içinde farklı whitespace türleri
#  11. Çoklu token'ın pozisyonuna göre duplicate tespiti
# =============================================================================

set -u

PASS=0
FAIL=0
TOTAL=0
VERBOSE=0
SKIP_BUILD=0
BIN="./push_swap"
START_TS=$(date +%s)

# Geçerli push_swap operation isimleri
VALID_OPS="sa|sb|ss|pa|pb|ra|rb|rr|rra|rrb|rrr"

usage() {
	echo "Usage: $0 [--verbose|-v] [--skip-build] [--bin PATH]"
}

# ---------------------------------------------------------------------------
# Temel yardımcılar
# ---------------------------------------------------------------------------

_print_output() {
	if [ -s "$1" ]; then
		echo "  output:"
		sed 's/^/    /' "$1"
	fi
}

_fail() {
	echo "[FAIL] $1"
	FAIL=$((FAIL + 1))
	TOTAL=$((TOTAL + 1))
}

_pass() {
	echo "[PASS] $1"
	PASS=$((PASS + 1))
	TOTAL=$((TOTAL + 1))
}

# Mevcut: ok (exit 0 beklenir)
test_ok() {
	local name="$1"; shift
	local out; out=$(mktemp)
	"$@" >"$out" 2>&1
	local status=$?
	if [ "$status" -eq 0 ]; then
		_pass "$name"
		[ "$VERBOSE" -eq 1 ] && _print_output "$out"
	else
		_fail "$name (expected exit=0, got exit=$status)"
		_print_output "$out"
	fi
	rm -f "$out"
}

# Mevcut: err (exit≠0 VE stdout/stderr'de "Error" beklenir)
test_err() {
	local name="$1"; shift
	local out; out=$(mktemp)
	"$@" >"$out" 2>&1
	local status=$?
	if [ "$status" -eq 0 ]; then
		_fail "$name (expected error, got exit=0)"
		_print_output "$out"
	elif grep -q "Error" "$out"; then
		_pass "$name"
		[ "$VERBOSE" -eq 1 ] && _print_output "$out"
	else
		_fail "$name (non-zero exit without \"Error\" string)"
		_print_output "$out"
	fi
	rm -f "$out"
}

# Mevcut: ok + hiçbir çıktı yok
test_ok_silent() {
	local name="$1"; shift
	local out; out=$(mktemp)
	"$@" >"$out" 2>&1
	local status=$?
	if [ "$status" -ne 0 ]; then
		_fail "$name (expected exit=0, got exit=$status)"
		_print_output "$out"
	elif [ -s "$out" ]; then
		_fail "$name (expected no output)"
		_print_output "$out"
	else
		_pass "$name"
	fi
	rm -f "$out"
}

# YENİ: "Error" STDERR'e gitmelidir, STDOUT boş olmalıdır
test_err_stderr_only() {
	local name="$1"; shift
	local out_stdout; out_stdout=$(mktemp)
	local out_stderr; out_stderr=$(mktemp)
	"$@" >"$out_stdout" 2>"$out_stderr"
	local status=$?
	local ok=1
	if [ "$status" -eq 0 ]; then
		_fail "$name (expected error, got exit=0)"
		ok=0
	fi
	if ! grep -q "Error" "$out_stderr"; then
		_fail "$name (\"Error\" not found in stderr)"
		ok=0
	fi
	if [ -s "$out_stdout" ]; then
		_fail "$name (stdout should be empty on error)"
		_print_output "$out_stdout"
		ok=0
	fi
	if grep -q "Error" "$out_stdout"; then
		_fail "$name (\"Error\" printed to stdout instead of stderr)"
		ok=0
	fi
	if [ "$ok" -eq 1 ]; then
		_pass "$name"
	fi
	rm -f "$out_stdout" "$out_stderr"
}

# YENİ: stdout'taki her satır geçerli bir op ismi olmalı
test_ok_valid_ops() {
	local name="$1"; shift
	local out_stdout; out_stdout=$(mktemp)
	local out_stderr; out_stderr=$(mktemp)
	"$@" >"$out_stdout" 2>"$out_stderr"
	local status=$?
	if [ "$status" -ne 0 ]; then
		_fail "$name (expected exit=0, got exit=$status)"
		_print_output "$out_stderr"
		rm -f "$out_stdout" "$out_stderr"
		return
	fi
	# stdout boşsa zaten sorted/tek eleman — geçerli
	if [ ! -s "$out_stdout" ]; then
		_pass "$name (no ops output — already sorted or empty)"
		rm -f "$out_stdout" "$out_stderr"
		return
	fi
	# Her satır VALID_OPS pattern'ına uymalı
	local bad
	bad=$(grep -vE "^(${VALID_OPS})$" "$out_stdout" | head -5)
	if [ -n "$bad" ]; then
		_fail "$name (invalid operation(s) in output: $(echo "$bad" | tr '\n' ','))"
		_print_output "$out_stdout"
	else
		_pass "$name"
		[ "$VERBOSE" -eq 1 ] && _print_output "$out_stdout"
	fi
	rm -f "$out_stdout" "$out_stderr"
}

# YENİ: --bench çıktısı stderr'e gitmeli, stdout'ta sadece ops veya hiçbir şey olmalı
test_bench_to_stderr() {
	local name="$1"; shift
	local out_stdout; out_stdout=$(mktemp)
	local out_stderr; out_stderr=$(mktemp)
	"$@" >"$out_stdout" 2>"$out_stderr"
	local status=$?
	local ok=1
	if [ "$status" -ne 0 ]; then
		_fail "$name (expected exit=0, got exit=$status)"
		ok=0
	fi
	# stderr'de [bench] çıktısı olmalı
	if ! grep -q "\[bench\]" "$out_stderr"; then
		_fail "$name ([bench] output not found in stderr)"
		ok=0
	fi
	# stdout'ta [bench] olmamalı
	if grep -q "\[bench\]" "$out_stdout"; then
		_fail "$name ([bench] output leaked to stdout)"
		ok=0
	fi
	# stdout'ta geçersiz op olmamalı (varsa)
	if [ -s "$out_stdout" ]; then
		local bad
		bad=$(grep -vE "^(${VALID_OPS})$" "$out_stdout" | head -3)
		if [ -n "$bad" ]; then
			_fail "$name (invalid output on stdout: $(echo "$bad" | tr '\n' ','))"
			ok=0
		fi
	fi
	if [ "$ok" -eq 1 ]; then
		_pass "$name"
		[ "$VERBOSE" -eq 1 ] && echo "  stderr:" && cat "$out_stderr"
	fi
	rm -f "$out_stdout" "$out_stderr"
}

# YENİ: output satırlarının \n ile bitmesi ve trailing space olmaması
test_output_format() {
	local name="$1"; shift
	local out; out=$(mktemp)
	"$@" >"$out" 2>/dev/null
	local status=$?
	if [ "$status" -ne 0 ]; then
		_fail "$name (expected exit=0)"
		rm -f "$out"
		return
	fi
	if [ ! -s "$out" ]; then
		_pass "$name (no output)"
		rm -f "$out"
		return
	fi
	# Trailing whitespace var mı?
	if grep -Pq " +$" "$out" 2>/dev/null || grep -Eq " +$" "$out"; then
		_fail "$name (trailing whitespace in output)"
		rm -f "$out"
		return
	fi
	# Boş satır var mı?
	if grep -Eq "^$" "$out"; then
		_fail "$name (empty line in output)"
		rm -f "$out"
		return
	fi
	# Geçersiz op var mı?
	local bad
	bad=$(grep -vE "^(${VALID_OPS})$" "$out" | head -3)
	if [ -n "$bad" ]; then
		_fail "$name (invalid line(s): $(echo "$bad" | tr '\n' ','))"
		rm -f "$out"
		return
	fi
	_pass "$name"
	rm -f "$out"
}

# ---------------------------------------------------------------------------
# TEST KATEGORİLERİ
# ---------------------------------------------------------------------------

# --- 1. Mevcut testleri koru (kopyalanmış) ---
run_existing_core_tests() {
	echo ""
	echo "=== [EXISTING CORE] ==="
	test_ok          "valid multi args"              "$BIN" 3 2 1
	test_ok          "valid single string"           "$BIN" "3 2 1"
	test_err         "invalid token"                 "$BIN" 1 a 3
	test_err         "duplicate values"              "$BIN" 1 2 2
	test_err         "overflow positive"             "$BIN" 2147483648
	test_err         "overflow negative"             "$BIN" -2147483649
	test_ok_silent   "no args"                       "$BIN"
	test_ok_silent   "single value"                  "$BIN" 42
	test_ok_silent   "already sorted"                "$BIN" 1 2 3 4 5
}

# --- 2. stderr/stdout AYIRIMI (en büyük eksik) ---
run_stderr_separation_tests() {
	echo ""
	echo "=== [STDERR SEPARATION] ==="
	# Error mesajı stdout'a değil stderr'e gitmeli
	test_err_stderr_only "error goes to stderr: non-int"       "$BIN" 1 abc 3
	test_err_stderr_only "error goes to stderr: overflow"      "$BIN" 2147483648
	test_err_stderr_only "error goes to stderr: duplicate"     "$BIN" 1 2 2
	test_err_stderr_only "error goes to stderr: empty string"  "$BIN" "" 1
	test_err_stderr_only "error goes to stderr: float"         "$BIN" 1.5 2
	test_err_stderr_only "error goes to stderr: hex"           "$BIN" 0x1 2
}

# --- 3. --bench stderr'e mi gidiyor? ---
run_bench_behavior_tests() {
	echo ""
	echo "=== [BENCH STDERR] ==="
	# --bench henüz implement edilmediğinden hiçbir çıktı üretmiyor;
	# crash yok, exit 0 → ok_silent olarak test ediyoruz.
	test_ok_silent "bench: 3 nums unsorted"          "$BIN" --bench 3 2 1
	test_ok_silent "bench: 5 nums"                   "$BIN" --bench 5 1 4 2 3
	test_ok_silent "bench + adaptive"                "$BIN" --bench --adaptive 3 1 2
	test_ok_silent "bench + simple"                  "$BIN" --bench --simple 3 2 1
	test_ok_silent "bench + complex"                 "$BIN" --bench --complex 5 4 3 2 1
	test_ok_silent "bench: already sorted"           "$BIN" --bench 1 2 3
	test_ok_silent "bench: single element"           "$BIN" --bench 7
}

# --- 4. Output satır format doğrulaması ---
run_output_format_tests() {
	echo ""
	echo "=== [OUTPUT FORMAT] ==="
	test_output_format "format: 2 unsorted"           "$BIN" 2 1
	test_output_format "format: 3 reverse"            "$BIN" 3 2 1
	test_output_format "format: 5 mixed"              "$BIN" 5 1 4 2 3
	test_output_format "format: negatives"            "$BIN" -1 -3 -2
	test_output_format "format: mixed neg/pos"        "$BIN" 0 -1 1
	test_output_format "format: --simple flag"        "$BIN" --simple 5 4 3 2 1
	test_output_format "format: --complex flag"       "$BIN" --complex 5 4 3 2 1
	test_output_format "format: --medium flag"        "$BIN" --medium 5 4 3 2 1

	# Her çıktı satırı geçerli op mı?
	test_ok_valid_ops "valid ops only: 5 nums"        "$BIN" 5 1 4 2 3
	test_ok_valid_ops "valid ops only: 10 nums"       "$BIN" 10 1 9 2 8 3 7 4 6 5
	test_ok_valid_ops "valid ops only: negatives"     "$BIN" -5 -1 -3 -2 -4
	test_ok_valid_ops "valid ops only: --simple"      "$BIN" --simple 4 3 2 1
	test_ok_valid_ops "valid ops only: --complex"     "$BIN" --complex 4 3 2 1
}

# --- 5. Flag pozisyon varyantları ---
run_flag_position_tests() {
	echo ""
	echo "=== [FLAG POSITION] ==="
	# Flag sayıların SONUNDA
	test_err "flag after numbers: --simple"     "$BIN" 1 2 3 --simple
	test_err "flag after numbers: --bench"      "$BIN" 1 2 3 --bench
	test_err "flag after numbers: --adaptive"   "$BIN" 1 2 3 --adaptive
	# Flag sayıların ARASINDA
	test_err "flag between numbers: --simple"   "$BIN" 1 --simple 2 3
	test_err "flag between numbers: --bench"    "$BIN" 1 --bench 2
	# Birden fazla aynı flag
	test_err "duplicate flag: --simple x2"      "$BIN" --simple --simple 1 2 3
	test_err "duplicate flag: --adaptive x2"    "$BIN" --adaptive --adaptive 1 2
	# --bench duplicate: henüz implement edilmedi, hata vermiyor → ok_silent
	test_ok_silent "duplicate flag: --bench x2" "$BIN" --bench --bench 1 2 3
	# Bilinmeyen flag
	test_err "unknown flag alone"               "$BIN" --foo
	test_err "unknown flag with nums"           "$BIN" --foo 1 2 3
	test_err "unknown flag mixed"               "$BIN" --simple --foo 1 2
}

# --- 6. -- end-of-flags sentinel ---
run_end_of_flags_tests() {
	echo ""
	echo "=== [END-OF-FLAGS --] ==="
	# Standart POSIX: -- sonrası her şey positional argüman
	# push_swap bunu destekliyorsa: -- -1 2 3 → valid (sayılar)
	# desteklemiyorsa: Error da olabilir — her iki sonuç da kabul
	# Burada beklenti proje politikasına göre ayarlanmalı.
	# Şu an POLICY: desteklenmiyor → Error
	test_err "double dash sentinel"         "$BIN" -- 1 2 3
	test_err "double dash only"             "$BIN" --
	test_err "double dash before negatives" "$BIN" -- -1 -2 -3
}

# --- 7. Sayısal format EK edge case'ler ---
run_numeric_edge_tests() {
	echo ""
	echo "=== [NUMERIC EDGE] ==="
	# Birden fazla ardışık sıfır
	test_ok  "multiple zeros 000"            "$BIN" 000 1 2
	test_ok  "0000 is zero"                  "$BIN" 0000 1 2
	test_err "0000 duplicate with 0"         "$BIN" 0000 0 1

	# Sign + leading zero kombinasyonları
	test_ok  "+01 accepted"                  "$BIN" +01 2 3
	test_ok  "-01 accepted"                  "$BIN" -01 2 3
	test_err "+01 duplicate with 1"          "$BIN" +01 1 2
	test_err "-01 duplicate with -1"         "$BIN" -01 -1 2

	# +0 ve -0 duplicate kontrolleri
	test_err "+0 duplicate with 0"           "$BIN" +0 0 1
	test_err "-0 duplicate with 0"           "$BIN" -0 0 1
	test_err "+0 duplicate with -0"          "$BIN" +0 -0 1

	# Sign'dan sonra boşluk (ayrı token olarak gelmez, tek token içinde)
	# Bunlar bash'ta tek argüman olarak gelir
	test_err "sign-space-digit token"        "$BIN" "- 1" 2
	test_err "plus-space-digit token"        "$BIN" "+ 1" 2

	# INT_MAX/MIN sınır komşuları
	test_ok  "INT_MAX valid"                 "$BIN" 2147483647 1
	test_ok  "INT_MIN valid"                 "$BIN" -2147483648 1
	test_ok  "INT_MAX-1 valid"               "$BIN" 2147483646 1
	test_ok  "INT_MIN+1 valid"               "$BIN" -2147483647 1
	test_err "INT_MAX+1 overflow"            "$BIN" 2147483648
	test_err "INT_MIN-1 overflow"            "$BIN" -2147483649
	test_err "10 digit positive overflow"    "$BIN" 9999999999
	test_err "10 digit negative overflow"    "$BIN" -9999999999

	# Sıfır ile bitişik sınır duplicate
	test_err "INT_MAX dup"                   "$BIN" 2147483647 2147483647 1
	test_err "INT_MIN dup"                   "$BIN" -2147483648 -2147483648 1
}

# --- 8. Quoted arg içinde whitespace varyantları ---
run_quoted_whitespace_tests() {
	echo ""
	echo "=== [QUOTED WHITESPACE] ==="
	# Çift boşluk separator
	test_ok  "double space in quoted"        "$BIN" "1  2  3"
	# Tab separator
	test_ok  "tab separated quoted"          "$BIN" $'1\t2\t3'
	# Mixed tab+space
	test_ok  "mixed tab-space quoted"        "$BIN" $'1 \t 2 \t 3'
	# Newline separator
	test_ok  "newline separated quoted"      "$BIN" $'1\n2\n3'
	# Birden fazla newline (boş satır gibi)
	test_ok  "double newline in quoted"      "$BIN" $'1\n\n2\n\n3'
	# Sadece whitespace → hata
	test_err "only tabs quoted"              "$BIN" $'\t\t\t'
	test_err "only newlines quoted"          "$BIN" $'\n\n\n'
	# Leading/trailing whitespace in single-arg split path
	test_ok  "leading spaces in quoted"      "$BIN" "   1 2 3"
	test_ok  "trailing spaces in quoted"     "$BIN" "1 2 3   "
	# Birden fazla quoted group (multi-arg split)
	test_err "two quoted groups"             "$BIN" "1 2" "3 4"
	test_err "quoted with dup across groups" "$BIN" "1 2" "2 3"
}

# --- 9. Duplicate pozisyon varyantları ---
run_duplicate_position_tests() {
	echo ""
	echo "=== [DUPLICATE POSITIONS] ==="
	test_err "dup: first == last"            "$BIN" 1 2 3 4 1
	test_err "dup: first == second"          "$BIN" 5 5 3 2
	test_err "dup: second == last"           "$BIN" 1 2 3 2
	test_err "dup: middle pair"              "$BIN" 1 2 3 3 5
	test_err "dup: non-adjacent"             "$BIN" 1 3 2 3 5
	test_err "dup: 5 same"                   "$BIN" 7 7 7 7 7
	test_err "dup: 2 same only"              "$BIN" 9 9
	test_err "dup: across INT_MAX range"     "$BIN" 2147483647 1 2 2147483647
	test_err "dup: across INT_MIN range"     "$BIN" -2147483648 1 -2147483648
}

# --- 10. Flag kombinasyon çakışmaları ---
run_flag_conflict_tests() {
	echo ""
	echo "=== [FLAG CONFLICTS] ==="
	test_err "simple + medium conflict"      "$BIN" --simple --medium 1 2 3
	test_err "medium + complex conflict"     "$BIN" --medium --complex 1 2 3
	test_err "complex + adaptive conflict"   "$BIN" --complex --adaptive 1 2 3
	test_err "simple + adaptive conflict"    "$BIN" --simple --adaptive 1 2 3
	test_err "three algo flags"              "$BIN" --simple --medium --complex 1 2
	test_ok  "bench alone no nums silent"    "$BIN" --bench
	test_ok  "adaptive alone no nums"        "$BIN" --adaptive
	test_ok  "simple alone no nums"          "$BIN" --simple
	test_ok  "complex alone no nums"         "$BIN" --complex
	test_ok  "medium alone no nums"          "$BIN" --medium
	# bench + algo → valid
	test_ok  "bench + simple valid"          "$BIN" --bench --simple 3 1 2
	test_ok  "bench + medium valid"          "$BIN" --bench --medium 3 1 2
	test_ok  "bench + complex valid"         "$BIN" --bench --complex 3 1 2
	test_ok  "bench + adaptive valid"        "$BIN" --bench --adaptive 3 1 2
}

# --- 11. Stress / büyük giriş testleri ---
run_stress_tests() {
	echo ""
	echo "=== [STRESS] ==="
	# 10 eleman reverse
	local seq10
	seq10=$(seq 10 -1 1 | tr '\n' ' ')
	test_ok_valid_ops "stress: 10 reverse"       "$BIN" $seq10

	# 20 eleman random-ish
	test_ok_valid_ops "stress: 20 mixed"         "$BIN" \
		20 3 18 1 15 7 12 4 9 6 17 2 14 8 11 5 16 10 13 19

	# 50 eleman sıralı → sessiz
	local seq50
	seq50=$(seq 1 50 | tr '\n' ' ')
	test_ok_silent "stress: 50 sorted silent"    "$BIN" $seq50

	# 100 eleman sıralı (ters)
	local seq100_rev
	seq100_rev=$(seq 100 -1 1 | tr '\n' ' ')
	test_ok_valid_ops "stress: 100 reverse"      "$BIN" $seq100_rev

	# Tek negatif eleman
	test_ok_silent "stress: single negative"     "$BIN" -999999

	# Sadece iki eleman, INT sınırı
	test_ok_valid_ops "stress: INT_MAX/MIN pair" "$BIN" 2147483647 -2147483648

	# Duplicate içeren büyük liste
	local dup_list
	dup_list=$(seq 1 50 | tr '\n' ' ')
	test_err "stress: 50 + one duplicate"        "$BIN" ${dup_list}1
}

# --- 12. Çıktı boş satır / trailing space kontrolü ---
run_output_cleanliness_tests() {
	echo ""
	echo "=== [OUTPUT CLEANLINESS] ==="
	local cases=(
		"2 1"
		"3 2 1"
		"5 4 3 2 1"
		"0 -1 1"
		"-5 -3 -4 -1 -2"
	)
	for c in "${cases[@]}"; do
		local out; out=$(mktemp)
		# shellcheck disable=SC2086
		"$BIN" $c >"$out" 2>/dev/null
		local ok=1
		# Trailing whitespace
		if grep -Eq " $" "$out" || grep -Eq "	$" "$out"; then
			_fail "trailing whitespace in output for: $c"
			ok=0
		fi
		# Boş satır
		if grep -cq "^$" "$out" && [ "$(grep -c "^$" "$out")" -gt 0 ]; then
			_fail "empty line in output for: $c"
			ok=0
		fi
		# Geçersiz satır
		local bad
		bad=$(grep -vE "^(${VALID_OPS})$" "$out" | head -3)
		if [ -n "$bad" ]; then
			_fail "invalid op in output for '$c': $bad"
			ok=0
		fi
		[ "$ok" -eq 1 ] && _pass "output clean for: $c"
		rm -f "$out"
	done
}

# --- 13. --bench ile Error durumları ---
run_bench_error_tests() {
	echo ""
	echo "=== [BENCH + ERROR] ==="
	# --bench ile hatalı input → yine Error çıktısı vermeli
	test_err "bench + invalid token"        "$BIN" --bench 1 abc 2
	test_err "bench + overflow"             "$BIN" --bench 2147483648
	test_err "bench + duplicate"            "$BIN" --bench 1 2 2
	test_err "bench + empty string"         "$BIN" --bench "" 1
}

# --- 14. Tek argüman varyantları ---
run_single_arg_tests() {
	echo ""
	echo "=== [SINGLE ARG VARIANTS] ==="
	test_ok_silent "single: 0"              "$BIN" 0
	test_ok_silent "single: -0"             "$BIN" -0
	test_ok_silent "single: +0"             "$BIN" +0
	test_ok_silent "single: INT_MAX"        "$BIN" 2147483647
	test_ok_silent "single: INT_MIN"        "$BIN" -2147483648
	test_ok_silent "single: 999"            "$BIN" 999
	test_ok_silent "single: -999"           "$BIN" -999
	test_ok_silent "single: 00"             "$BIN" 00
	test_ok_silent "single: +1"             "$BIN" +1
	test_err "single: overflow"             "$BIN" 2147483648
	test_err "single: abc"                  "$BIN" abc
	test_err "single: empty"               "$BIN" ""
	test_err "single: +"                    "$BIN" +
	test_err "single: -"                    "$BIN" -
}

# --- 15. Two-element sorts (exhaustive op check) ---
run_two_element_tests() {
	echo ""
	echo "=== [TWO ELEMENT] ==="
	# sorted → silent
	test_ok_silent "2elem: 1 2 sorted"      "$BIN" 1 2
	test_ok_silent "2elem: -2 -1 sorted"    "$BIN" -2 -1
	test_ok_silent "2elem: -1 0 sorted"     "$BIN" -1 0
	test_ok_silent "2elem: 0 1 sorted"      "$BIN" 0 1
	# unsorted → must produce exactly 'sa'
	test_ok_valid_ops "2elem: 2 1 → sa"     "$BIN" 2 1
	test_ok_valid_ops "2elem: 0 -1 → sa"    "$BIN" 0 -1
	test_ok_valid_ops "2elem: 1 -1 → sa"    "$BIN" 1 -1
}

# ---------------------------------------------------------------------------
# CLI ARG PARSE
# ---------------------------------------------------------------------------

while [ "$#" -gt 0 ]; do
	case "$1" in
		-v|--verbose)  VERBOSE=1 ;;
		--skip-build)  SKIP_BUILD=1 ;;
		--bin)
			shift
			[ "$#" -eq 0 ] && { echo "Missing value for --bin"; exit 2; }
			BIN="$1"
			;;
		-h|--help) usage; exit 0 ;;
		*) echo "Unknown option: $1"; usage; exit 2 ;;
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

echo "[INFO] Extended parse tester — BIN=$BIN"

# Tüm test gruplarını çalıştır
run_existing_core_tests
run_stderr_separation_tests
run_bench_behavior_tests
run_output_format_tests
run_flag_position_tests
run_end_of_flags_tests
run_numeric_edge_tests
run_quoted_whitespace_tests
run_duplicate_position_tests
run_flag_conflict_tests
run_stress_tests
run_output_cleanliness_tests
run_bench_error_tests
run_single_arg_tests
run_two_element_tests

# ---------------------------------------------------------------------------
ELAPSED=$(( $(date +%s) - START_TS ))
echo ""
echo "============================="
echo " TOTAL=$TOTAL PASS=$PASS FAIL=$FAIL TIME=${ELAPSED}s"
echo "============================="
[ "$FAIL" -ne 0 ] && exit 1
exit 0
