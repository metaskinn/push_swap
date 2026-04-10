*This activity has been created as part of the 42 curriculum by metaskin, asobolev.*

# push_swap

## Description
`push_swap` is a stack-sorting project built around a restricted set of operations.
The program reads a list of integers, chooses a sorting strategy at runtime, and
prints the resulting Push_swap instructions on standard output.

This repository includes four strategies:
- `--simple` for a selection-style $O(n^2)$ approach
- `--medium` for a chunk-based $O(n\sqrt{n})$ approach
- `--complex` for a radix-based $O(n \log n)$ approach
- `--adaptive` for disorder-based strategy selection

The default behavior is `--adaptive` when no selector is provided.

## Instructions

Build:
```bash
make
```

Clean:
```bash
make clean
make fclean
make re
```

Run examples:
```bash
./push_swap 2 1 3 6 5 8
./push_swap --simple 5 4 3 2 1
./push_swap --medium 4 67 3 87 23
./push_swap --complex 4 67 3 87 23
./push_swap --adaptive 4 67 3 87 23
```

Benchmark mode:
```bash
./push_swap --bench --adaptive 5 4 3 2 1 2> bench.txt | ./checker_Mac 5 4 3 2 1
cat bench.txt
```

The benchmark report is printed on stderr and includes disorder, strategy,
complexity class, total operations, and per-operation counters.

## Algorithm Design

### Simple
The simple strategy is a selection-style extraction method. It repeatedly finds
the smallest remaining value, rotates it to the top, pushes it to stack `b`, and
finally restores all values to stack `a`. This is intentionally quadratic and is
used as the baseline for low-complexity behavior.

### Medium
The medium strategy uses chunk-based partitioning. Values are indexed, split into
chunks, and moved from `a` to `b` in a controlled order. The largest values are
then moved back to `a`. This keeps the operation count in the $O(n\sqrt{n})$
family for the project’s Push_swap model.

### Complex
The complex strategy uses an LSD radix adaptation on indexed values. It groups
numbers bit by bit and rebuilds the sorted stack after each pass. This gives a
predictable $O(n \log n)$-style operation bound in the Push_swap model.

### Adaptive
Adaptive first measures disorder, then dispatches to one of the three strategies:
- disorder < 0.2 -> simple
- 0.2 <= disorder < 0.5 -> medium
- disorder >= 0.5 -> complex

This matches the subject thresholds and keeps the runtime choice aligned with
the input shape.

## Complexity Notes

The project subject evaluates complexity in terms of Push_swap operations, not
classical array-based runtime. The disorder metric is computed before any moves.
The chosen thresholds are:
- low disorder: $O(n^2)$
- medium disorder: $O(n\sqrt{n})$
- high disorder: $O(n \log n)$

These thresholds are used by the adaptive strategy to select the most appropriate
method for the current input.

## Resources

- [42 Push_swap subject](all_team/team_resources/subject.md)
- [The Norm](all_team/team_resources/the_norm.md)
- [Big O notation](https://en.wikipedia.org/wiki/Big_O_notation)
- [Algorithm analysis](https://en.wikipedia.org/wiki/Analysis_of_algorithms)
- [Radix sort](https://en.wikipedia.org/wiki/Radix_sort)
- [Stacks](https://en.wikipedia.org/wiki/Stack_(abstract_data_type))

AI was used for code organization, refactoring support, benchmark reporting, and
document drafting. All generated suggestions were reviewed, tested, and adapted
before being kept.

## Contributors

**metaskin (Meltem Taşkın):**
- Adaptive algorithm design and implementation (`--adaptive` flag)
- Disorder calculation and measurement
- Benchmark mode feature (output formatting, operation counting)
- README documentation and project integration
- Algorithm complexity analysis and threshold tuning

**asobolev (Alex Sobolev):**
- Core stack operations: `push_op.c`, `swap_op.c`, `rotate_op.c`, `reverse_rotate_op.c`
- Sorting primitives: `simple_sort()` implementation
- Doubly-linked list data structure design (`stack.h`, `stack.c`)
- Node operations and memory management

## Notes

The repository includes a benchmark mode and a local checker script for testing.
All mandatory tests in this workspace currently pass.
