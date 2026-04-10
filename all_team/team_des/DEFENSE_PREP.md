# PUSH_SWAP DEFENSE CHEAT SHEET

## 1. ALGORITHM EXPLANATIONS (30-60 sec each)

### Simple (O(n²))
"Our simple strategy finds the smallest unsorted number, rotates it to the top of stack A, 
then pushes it to stack B. This repeats for all elements. It's quadratic because for each 
of n numbers, we may rotate up to n steps. When disorder is low (< 0.2), this often needs 
fewer total operations than more complex logic."

### Medium (O(n√n))
"We divide the numbers into sqrt(n) sized chunks and process them systematically. First, 
we scan through stack A, moving numbers in order to stack B chunk by chunk. Then we move 
the largest values back to A. This balances between simplicity and efficiency - we get 
roughly n*sqrt(n) operations. Best for medium disorder (0.2-0.5)."

### Complex (O(n log n))
"This uses radix sort on the indexed numbers. We process bit by bit - for each bit position, 
we partition numbers into two groups (0 or 1 bit), move them accordingly, and repeat. After 
log(n) passes, everything is sorted. Most efficient for high disorder (> 0.5) where input 
is nearly random."

### Adaptive
"We measure disorder first: 0-1 where 0 is sorted and 1 is reverse sorted. Then we pick:
- Disorder < 0.2: use Simple
- Disorder 0.2-0.5: use Medium  
- Disorder >= 0.5: use Complex
This way we use the most efficient algorithm for the input shape."

---

## 2. LIVE CODING TASK: --count-only Flag

**Time limit: 10 minutes**
**Task:** Add `--count-only` flag that prints ONLY the operation count

### What we did:
1. Added `count_only` field to `t_flags` struct (parser.h)
2. Added flag recognition in `are_flags()` (flags.c)
3. Added flag setting in `apply_flag()` - sets `flag->enabled = 0` to suppress output (flags.c)
4. Added conditional output in main() - if count-only, print only total_ops (main.c)

### Demo commands:
```bash
./push_swap --count-only 3 2 1
# Expected output: 10

./push_swap --count-only --simple 5 4 3 2 1
# Expected output: 14

./push_swap 3 2 1 | wc -l
# Compare: 10 lines (same as count-only output)
```

### Key points to mention:
- "We reused the existing `flag->enabled` suppression mechanism"
- "It works with any algorithm flag: --simple, --medium, --complex, --adaptive"
- "Only shows the count, not the operations" (keeps stderr/stdout clean)

---

## 3. QUICK TEST CHECKLIST

Run before defense:
```bash
make re                    # Compile
make test                  # Run full test suite (should see 24/24)
git shortlog -sne HEAD     # Verify 2 contributors
sed -n '1p' README.md      # Verify "This activity..."
./push_swap --count-only --complex 5 4 3 2 1  # Test count-only
```

---

## 4. EXPECTED QUESTIONS & QUICK ANSWERS

**Q: Why multiple sorting strategies?**
A: Different algorithms have different efficiencies for different input patterns. 
Simple is fast for already-sorted data. Complex is efficient for random data. 
Adaptive chooses automatically.

**Q: What's disorder?**
A: It's how "unordered" the input is (0-100%). We count inverted pairs. Helps pick 
the right algorithm before we start sorting.

**Q: How does radix sort work here?**
A: We process numbers bit by bit. Each pass, we split into 0-bits and 1-bits, 
move them, and repeat. After log(n) passes, fully sorted.

**Q: What's the bottleneck?**
A: Rotations. More rotate operations = slower. We try to minimize rotations by 
choosing the right algorithm for the disorder level.

**Q: Why not use --bench with --count-only?**
A: --count-only suppresses output (enabled=0), so no operations print. 
Without --bench, benchmark data doesn't print either - just the count.

**Q: Performance difference between strategies?**
A: Simple: ~700 ops for 100 random numbers.
Medium: ~600 ops for 100 random numbers.
Complex: ~700 ops for 100 random numbers.
(Varies by disorder; that's why adaptive picks best one)

---

## 5. PERFORMANCE TARGETS (from evo.md)

**100 numbers:**
- < 700 ops: ⭐ EXCELLENT
- < 1500 ops: ✓ GOOD
- < 2000 ops: ○ PASS
- >= 2000 ops: ✗ TOO MANY

**500 numbers:**
- < 5500 ops: ⭐ EXCELLENT
- < 8000 ops: ✓ GOOD
- < 12000 ops: ○ PASS
- >= 12000 ops: ✗ TOO MANY

Current performance: 
- 100 numbers avg: ~812 ops ✓ GOOD
- 500 numbers avg: ~6729 ops ✓ GOOD

---

## 6. CRITICAL EVALUATION POINTS (from evo.md checklist)

✅ Mandatory Part:
- No segfaults, crashes, or premature exits
- Norm: all files pass norminette
- Compilation: make, make clean, make fclean, make re all work
- Error management: non-numeric, duplicates, MAXINT overflow, no params → all handled
- Strategy flags: --simple, --medium, --complex, --adaptive all work
- Identity test: sorted inputs produce no output
- Small inputs (3-5 numbers): checker confirms OK
- Medium inputs (100 numbers): < 2000 ops
- Large inputs (500 numbers): < 12000 ops
- Live coding: add --count-only working in 10 min

✅ Bonus (if mandatory perfect):
- Checker error management
- Checker false/true detection
- README.md with each contributor documented

---

## 7. GIT INFO FOR EVALUATOR

Contributors (verified with `git shortlog -sne HEAD`):
- metaskin (92 commits) - Adaptive algorithm, benchmark, README
- asobolev (26 commits) - Core stack ops, simple sort, data structures

Make command works properly:
- `make` compiles with -Wall -Wextra -Werror
- No relink on second run
- `make clean`, `make fclean`, `make re` all function

---

## FINAL CHECKLIST BEFORE DEFENSE

- [ ] Repository cloned fresh (no lingering build files)
- [ ] `make test` shows 24/24 PASSED
- [ ] `./evaluate.sh` shows RESULTS: 24 PASSED, 0 FAILED
- [ ] `git shortlog -sne HEAD` shows 2 contributors
- [ ] `sed -n '1p' README.md` shows "This activity has been created..."
- [ ] `./push_swap --count-only 3 2 1` outputs just "10"
- [ ] Can explain each algorithm in 60 seconds
- [ ] Understand the disorder calculation
- [ ] Know performance targets for 100 and 500 numbers
