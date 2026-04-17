*This project has been created as part of the 42 curriculum by metaskin, asobolev.*

# push_swap

A stack-sorting project focused on algorithmic complexity under strict operation constraints.

## Contents
- [Description](#description)
- [Instructions](#instructions)
- [Algorithm Design](#algorithm-design)
- [Contributors](#contributors)
- [Resources](#resources)

## Description
`push_swap` sorts integers in stack **a** using only allowed Push Swap operations and an auxiliary stack **b**.

The project includes all mandatory strategy modes:

| Mode | Purpose | Target Complexity |
| :--- | :--- | :--- |
| `--simple` | Baseline strategy | `O(n^2)` |
| `--medium` | Chunk-oriented strategy | `O(n * sqrt(n))` |
| `--complex` | Radix-based strategy | `O(n log n)` |
| `--adaptive` (default) | Picks strategy by measured disorder | Depends on disorder |

### Benchmark mode
When `--bench` is enabled, metrics are printed to **stderr**:
- disorder (%)
- selected strategy and complexity class
- total operation count
- per-operation counters (`sa sb ss pa pb ra rb rr rra rrb rrr`)

Project goal: output a valid, efficient Push Swap instruction sequence that sorts stack **a** in ascending order.

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

### Run
```bash
./push_swap [--bench] [--simple|--medium|--complex|--adaptive] "3 2 1"
./push_swap [--bench] [--simple|--medium|--complex|--adaptive] 3 2 1
```

### Behavior rules
- If no strategy flag is provided, `--adaptive` is used.
- Any strategy flag works with any valid input size.
- Benchmark output appears only with `--bench` and is sent to **stderr**.
- If no arguments are provided, the program exits silently.
- Invalid input prints `Error` to **stderr**.
- Strategy flags must be provided before numeric arguments.

### Quick check
```bash
ARG="4 67 3 87 23"
./push_swap --complex $ARG
./push_swap --bench --adaptive $ARG 2> bench.txt
cat bench.txt
```

## Algorithm Design

### Disorder metric
Disorder is measured before sorting as inversion ratio:

`mistakes / total_pairs`

where:
- `mistakes` = number of inverted pairs
- `total_pairs = n * (n - 1) / 2`
- range is `[0, 1]`

### Simple strategy (`O(n^2)`)
Selection-like extraction:
1. Find minimum in stack `a`
2. Rotate or reverse-rotate `a` to top
3. Push to `b` with `pb`
4. Push all back to `a` with `pa`

### Medium strategy (`O(n * sqrt(n))`)
Chunk-based flow:
1. Assign rank indices
2. Push values from `a` to `b` using growing chunk limits
3. Optimize placement in `b` with `rb` when useful
4. Push back max-first to `a`

### Complex strategy (`O(n log n)`)
Index-based radix flow:
1. Assign rank indices
2. Process bits from LSB to MSB
3. Partition each pass using `pb` and `ra`
4. Push everything back with `pa` after each pass

### Adaptive strategy
Adaptive mode selects strategy by initial disorder:
- `disorder < 0.2` -> Simple (`O(n^2)`)
- `0.2 <= disorder < 0.5` -> Medium (`O(n * sqrt(n))`)
- `disorder >= 0.5` -> Complex (`O(n log n)`)

For very small inputs (`<= 5`), a dedicated small-sort routine is used.

Threshold rationale: values `0.2` and `0.5` come directly from subject-defined disorder ranges.

### Complexity rationale (Push Swap model)
- **Time:** measured by number of emitted operations.
- **Space:** stacks + metadata, overall `O(n)`.
- Complexity classes above are stated as upper-bound behavior in operation count.

## Contributors
- **metaskin**: argument/flag parser flow, complex strategy implementation, core stack structure
- **asobolev**: `atoi` and conversion utilities, split/tokenization utilities, simple and medium strategies

## Resources

- 42 GitBook overview: <https://42-cursus.gitbook.io/guide/2-rank-02/push_swap>
- Sorting algorithms overview: <https://en.wikipedia.org/wiki/Sorting_algorithm>
- Radix sort reference: <https://en.wikipedia.org/wiki/Radix_sort>
- Algorithm analysis and Big-O: <https://en.wikipedia.org/wiki/Analysis_of_algorithms>
- Stack ADT reference: <https://en.wikipedia.org/wiki/Stack_(abstract_data_type)>
- Asymptotic notation cheat sheet: <https://www.bigocheatsheet.com/>
- Community visualizer hint: search for "push_swap visualizer"

### AI usage
- AI was used only for README writing support and for learning algorithm concepts.
- AI was not used to generate project source code; all implementation decisions and code were produced and reviewed by the contributors.
