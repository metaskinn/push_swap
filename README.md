*This project has been created as part of the 42 curriculum by metaskin, asobolev.*

# push_swap

## Description
`push_swap` sorts integers in stack **a** using only allowed Push Swap operations and an auxiliary stack **b**.

This implementation includes all mandatory strategy modes required by the subject:
- `--simple` → Simple strategy (`O(n²)`)
- `--medium` → Medium strategy (`O(n * sqrt(n))`)
- `--complex` → Complex strategy (`O(n log n)`)
- `--adaptive` (default) → Chooses strategy from initial disorder

Optional benchmark mode (`--bench`) prints metrics to **stderr**:
- disorder (%)
- selected strategy and complexity class
- total operation count
- per-operation counters (`sa sb ss pa pb ra rb rr rra rrb rrr`)

## Instructions
### Build
```bash
make
```

### Clean
```bash
make clean
make fclean
make re
```

### Usage
```bash
./push_swap [--bench] [--simple|--medium|--complex|--adaptive] "3 2 1"
./push_swap [--bench] [--simple|--medium|--complex|--adaptive] 3 2 1
```

Notes:
- If no arguments are provided, program exits silently.
- On invalid input (non-integer, overflow, duplicates, malformed tokens), program prints `Error` to **stderr**.
- Flags must be provided before numeric arguments.

### Quick checks
```bash
ARG="4 67 3 87 23"
./push_swap --complex $ARG
./push_swap --bench --adaptive $ARG 2>bench.txt
cat bench.txt
```

## Algorithm Design
### Disorder metric
Disorder is computed before sorting as inversion ratio:
`mistakes / total_pairs`, range `[0, 1]`, where `mistakes` is the inversion count (out-of-order pairs) and `total_pairs = n * (n - 1) / 2`.

### Simple (`O(n²)`)
Selection-like extraction:
1. Find minimum in stack `a`
2. Rotate/reverse-rotate `a` to top
3. `pb` to `b`
4. `pa` all back to `a`

### Medium (`O(n * sqrt(n))` target)
Chunk-based strategy:
1. Assign rank indices
2. Push elements from `a` to `b` by growing chunk limit
3. Use `rb` placement optimization inside `b`
4. Push back max-first to `a`

### Complex (`O(n log n)` target)
Index-based radix approach:
1. Assign rank indices
2. Process bits from LSB to MSB
3. Partition each pass with `pb` / `ra`
4. `pa` all elements back after each pass

### Adaptive
Adaptive uses initial disorder thresholds:
- `disorder < 0.2` → Simple (`O(n²)`)
- `0.2 <= disorder < 0.5` → Medium (`O(n * sqrt(n))`)
- `disorder >= 0.5` → Complex (`O(n log n)`)

Special-case optimization: for very small inputs (`<= 5`), dedicated small-sort routine is used.

Rationale: this mapping follows the project requirement on adaptive complexity per disorder regime. The threshold values (`0.2` and `0.5`) are taken directly from the subject-defined disorder boundaries (`< 0.2`, `0.2-0.5`, `>= 0.5`).

### Complexity rationale (Push Swap operation model)
- **Time:** counted as number of emitted operations.
- **Space:** stacks + metadata (`O(n)` nodes plus per-node index).
- Strategy classes above describe upper-bound behavior in operation count for their intended regimes.

## Contributors
- **metaskin**
  - Argument/flag parser flow
  - Complex strategy implementation
  - Core stack structure
- **asobolev**
  - `atoi`/number conversion utilities
  - Split/tokenization utilities
  - Simple and medium strategy implementations

## Resources
- Push Swap Project Subject (42 School)
- Donald Knuth, *The Art of Computer Programming*, Volume 3: *Sorting and Searching*
- Big-O overview: <https://en.wikipedia.org/wiki/Analysis_of_algorithms>
- Stack ADT reference: <https://en.wikipedia.org/wiki/Stack_(abstract_data_type)>

## AI Usage
AI was used for:
- brainstorming README structure and phrasing,
- checking clarity of complexity explanations,
- verifying command examples and formatting.

All generated text/code suggestions were manually reviewed and adjusted before use.
