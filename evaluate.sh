#!/bin/bash

# Push_Swap Evaluation Test Suite
# Comprehensive test for peer evaluation

set +e  # Don't exit on errors

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

PASS=0
FAIL=0

test_name() {
    echo -e "\n${YELLOW}=== $1 ===${NC}"
}

pass() {
    echo -e "${GREEN}✓ PASS${NC}: $1"
    ((PASS++))
}

fail() {
    echo -e "${RED}✗ FAIL${NC}: $1"
    ((FAIL++))
}

# Pretest: Compilation
test_name "COMPILATION"
if make clean > /dev/null 2>&1 && make > /dev/null 2>&1; then
    pass "Compilation successful"
else
    fail "Compilation failed"
    exit 1
fi

# Test 1: Error - Non numeric
test_name "ERROR: Non-numeric parameter"
OUTPUT=$(./push_swap 5 4 "abc" 2 1 2>&1)
if echo "$OUTPUT" | grep -q "Error"; then
    pass "Correctly rejects non-numeric input"
else
    fail "Did not reject non-numeric input: $OUTPUT"
fi

# Test 2: Error - Duplicate
test_name "ERROR: Duplicate values"
OUTPUT=$(./push_swap 5 4 3 3 1 2>&1)
if echo "$OUTPUT" | grep -q "Error"; then
    pass "Correctly rejects duplicates"
else
    fail "Did not reject duplicates"
fi

# Test 3: Error - MAXINT overflow
test_name "ERROR: MAXINT overflow"
OUTPUT=$(./push_swap 5 99999999999 3 2 1 2>&1)
if echo "$OUTPUT" | grep -q "Error"; then
    pass "Correctly rejects MAXINT overflow"
else
    fail "Did not reject overflow: $OUTPUT"
fi

# Test 4: Error - No parameters
test_name "ERROR: No parameters"
OUTPUT=$(./push_swap 2>&1)
if [ -z "$OUTPUT" ]; then
    pass "No output on empty input"
else
    fail "Unexpected output on empty input: $OUTPUT"
fi

# Test 5: Strategy flags
test_name "STRATEGY SELECTION"
for flag in "--simple" "--medium" "--complex" "--adaptive"; do
    OPS=$(./push_swap $flag 5 4 3 2 1 2>/dev/null | wc -l | tr -d ' ')
    if [ "$OPS" -gt 0 ]; then
        pass "Flag $flag produces $OPS operations"
    else
        fail "Flag $flag produces no output"
    fi
done

# Test 6: Default adaptive
test_name "DEFAULT ADAPTIVE"
OPS=$(./push_swap 5 4 3 2 1 2>/dev/null | wc -l | tr -d ' ')
if [ "$OPS" -gt 0 ]; then
    pass "Default (no flag) produces adaptive output: $OPS ops"
else
    fail "Default produces no output"
fi

# Test 7: Identity - Already sorted
test_name "IDENTITY: Already sorted inputs"
for input in "42" "2 3" "0 1 2 3" "0 1 2 3 4 5"; do
    OPS=$(./push_swap $input 2>/dev/null | wc -l | tr -d ' ')
    if [ "$OPS" -eq 0 ]; then
        pass "Sorted '$input' produces 0 operations"
    else
        fail "Sorted '$input' produces $OPS operations (expected 0)"
    fi
done

# Test 8: Small input checker validation
test_name "VALIDATION: Small inputs with checker"
for input in "2 1 0" "0 2 1" "1 0 2"; do
    RESULT=$(./push_swap $input 2>/dev/null | ./checker_Mac $input 2>/dev/null)
    if echo "$RESULT" | grep -q "OK"; then
        pass "Checker confirms '$input' → OK"
    else
        fail "Checker failed for '$input': $RESULT"
    fi
done

# Test 9: Benchmark mode
test_name "BENCHMARK MODE"
OUTPUT=$(./push_swap --bench --simple 5 4 3 2 1 2>&1 | grep -c "\[bench\]")
if [ "$OUTPUT" -eq 5 ]; then
    pass "Benchmark produces 5 lines of output"
else
    fail "Benchmark produces $OUTPUT lines (expected 5)"
fi

# Verify benchmark format
if ./push_swap --bench --simple 5 4 3 2 1 2>&1 | grep -q "\[bench\] disorder:"; then
    pass "Benchmark includes disorder metric"
else
    fail "Missing disorder in benchmark"
fi

if ./push_swap --bench --simple 5 4 3 2 1 2>&1 | grep -q "\[bench\] strategy:"; then
    pass "Benchmark includes strategy name"
else
    fail "Missing strategy in benchmark"
fi

if ./push_swap --bench --simple 5 4 3 2 1 2>&1 | grep -q "\[bench\] total_ops:"; then
    pass "Benchmark includes total ops count"
else
    fail "Missing total_ops in benchmark"
fi

# Test 10: Edge case - Empty string
test_name "EDGE CASES"
OUTPUT=$(./push_swap "" 2>&1)
if echo "$OUTPUT" | grep -q "Error"; then
    pass "Empty string correctly returns Error"
else
    fail "Empty string handling failed"
fi

# Test 11: Disorder calculation
test_name "DISORDER CALCULATION"
# Reverse sorted should have high disorder
OUTPUT=$(./push_swap --bench --simple 5 4 3 2 1 2>&1 | grep disorder)
if echo "$OUTPUT" | grep -qE "disorder: [6-9][0-9]|disorder: 100"; then
    pass "Reverse sorted input has high disorder: $OUTPUT"
else
    fail "Disorder calculation seems off: $OUTPUT"
fi

# Test 12: Operation types
test_name "OPERATION TRACKING"
OUTPUT=$(./push_swap --bench --simple 3 2 1 2>&1 | grep "sa:\|pa:\|pb:")
if [ ! -z "$OUTPUT" ]; then
    pass "Operation counts tracked: $OUTPUT"
else
    fail "No operation counts in benchmark"
fi

# Summary
echo -e "\n${YELLOW}═════════════════════════════════════${NC}"
echo -e "RESULTS: ${GREEN}$PASS PASSED${NC}, ${RED}$FAIL FAILED${NC}"
echo -e "${YELLOW}═════════════════════════════════════${NC}"

if [ $FAIL -eq 0 ]; then
    echo -e "${GREEN}✓ All tests passed! Ready for evaluation.${NC}"
    exit 0
else
    echo -e "${RED}✗ Some tests failed. Review above.${NC}"
    exit 1
fi
