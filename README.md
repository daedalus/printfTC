# Turing Completeness of C printf

Does `printf` have enough computational power to be Turing complete on its own?
The answer is nuanced, and this repository explores exactly where the boundary
lies.

## The Honest Claim

**printf the format-string language is not Turing complete.** It has no loop
constructs, no conditionals, and no ability to call itself. A single `printf()`
call parses its format string left-to-right exactly once.

**But `%n` changes everything.** It writes an attacker-controlled value to an
arbitrary address. When that address is a return address or function pointer,
the format string hijacks control flow — and suddenly the format string *is*
the program. This is not hypothetical; it is exactly how real exploits work.

This repository demonstrates both sides:

| Claim | Status | Examples |
|-------|--------|----------|
| "printf + C is TC" | Proven (trivially — C is already TC) | #1–#15 |
| "printf alone is TC" | Requires `%n` to hijack control flow | #16 |
| "`%n` enables arbitrary write" | Proven — the real security finding | #1, #4, #7, #9 |

## What `%n` Actually Provides

```c
int sum = 0;
printf("%*s%*s%n", a, "", b, "", &sum);  // sum = a + b
```

`%*s` prints exactly N spaces (when the string is `""`), and `%n` writes the
cumulative character count to `sum`. This is a **read-modify-write cycle**:

| Primitive | Mechanism | Limitation |
|-----------|-----------|-----------|
| LOAD | `%*s` reads stored value as width | Only as format-string width arg |
| STORE | `%n` writes char count to any `int*` | Can only add to running count |
| Addition | Concatenate two `%*s` in one call | Works — pure printf |
| Subtraction | Cannot be done by printf alone | Requires C's `-=` after LOAD |
| Branching | Not in the format string language | Requires C's `if`/`else` |
| Looping | Not in the format string language | Requires C's `for`/`while` |

printf's `%n` is a **memory bus**, not an ALU. It provides the read/write
primitives. Arithmetic and control flow come from C.

## Building and Running

```bash
make all          # compile all examples
make clean        # remove binaries

./01_counter      # run individual example
./16_self Interpreter
```

Requires `gcc` with C11 support. Example #16 requires a non-NX stack
(disable ASLR and exec-stack for testing: `execstack -s ./16_self`).

## Examples

### Printf + C (demonstrate printf's memory primitives)

| # | File | What it demonstrates |
|---|------|----------------------|
| 1 | `src/01_counter.c` | Basic `%n` — writing character count to memory |
| 2 | `src/02_two_counter.c` | Minsky machine (2-counter, proven TC via C loops) |
| 3 | `src/03_fibonacci.c` | Iterative Fibonacci via printf addition |
| 4 | `src/04_calculator.c` | ALU: add (pure printf), sub (printf + C), mul, div, mod, pow |
| 5 | `src/05_conditional.c` | Conditional logic: min, max, abs, sign |
| 6 | `src/06_state_machine.c` | Finite automaton recognizing {a^n b^n | n >= 0} |
| 7 | `src/07_pointer_arithmetic.c` | Array init, sum, and 2x2 matrix multiply |
| 8 | `src/08_self_modifying.c` | Dynamic format strings and a data-driven interpreter |
| 9 | `src/09_memory_simulation.c` | CPU simulator: registers, RAM, instruction cycle |
| 10 | `src/10_ackermann.c` | Ackermann function (non-primitive-recursive) |
| 11 | `src/11_turing_machine.c` | Binary increment Turing machine |
| 12 | `src/12_lambda_calculus.c` | Church numerals, SUCC/ADD/MULT/EXP/PRED/SUB, booleans, fib |
| 13 | `src/13_formal_proof.c` | Brainfuck interpreter (minimal TC language) |
| 14 | `src/14_universal_machine.c` | Universal Turing machine (transition table as data) |
| 15 | `src/15_complex_example.c` | 4-element sorting network |

### Pure format-string TC (via `%n` control-flow hijack)

| # | File | What it demonstrates |
|---|------|----------------------|
| 16 | `src/16_self_interpreter.c` | Format string that interprets itself via `%n` return-address overwrite |

## How It Works

### Arithmetic via `%n`

```c
// Addition: pure printf — print a+b spaces, capture total
int sum = 0;
printf("%*s%*s%n", a, "", b, "", &sum);

// Subtraction: printf loads a via %n, C subtracts b
int diff = 0;
printf("%*s%n", a, "", &diff);
diff -= b;

// Multiplication: repeated addition
int product = 0;
for (int i = 0; i < b; i++)
    product = add(product, a);
```

Note: `%*d` with value 0 prints `"0"` (1 character), causing an off-by-one.
Always use `%*s` with `""` to print exactly N characters.

### Memory Access via `%n`

```c
int ram[256] = {0};
int *cell = &ram[address];
printf("%*s%n", value, "", cell);  // ram[address] = value
```

### The Control-Flow Hijack (what makes it truly TC)

A single `printf(input)` call where `input` is attacker-controlled can use `%n`
to overwrite the return address on the stack, jumping execution back to the
printf call. The format string then modifies its own arguments (or the program
state) before the next iteration. This creates a loop without any C `for`/`while`:

```
printf(input)  →  %n overwrites return addr  →  jumps back to printf
    →  %n modifies program state  →  %n overwrites return addr again  →  ...
```

This is the mechanism behind real format-string exploits and is the only
path to genuine Turing completeness for printf alone.

### Pitfalls

- **Use `%*s`, not `%*d`**: `printf("%*d", 0, 0)` prints `"0"` (1 char), breaking zero-operand cases. `printf("%*s", 0, "")` prints nothing (0 chars).
- **Single call for accumulation**: `%n` captures the count of *that* printf call only. Looping separate printf calls then capturing gives the last call's count (0), not the accumulated total. Combine into one call.
- **Negative width ≠ subtraction**: Per the C standard, a negative `%*` argument means left-justify with `abs(width)`. It does not shrink output.

## Computational Hierarchy

```
printf alone (no %n hijack)
    |
    | can only: load, store, add (one pass, no loops)
    v
Finite-state transducer  ← NOT Turing complete

printf + C control flow
    |
    | can: load, store, add, subtract, branch, loop
    v
Minsky Machine (2-counter) --- proven TC (Minsky, 1967)
    |
    | simulates
    v
Turing Machine
    |
    | equivalent to
    v
Lambda Calculus

printf with %n return-address hijack
    |
    | can: load, store, add, branch, loop (all in format string)
    v
Turing complete (architecture-specific)
```

## What the 15+1 Examples Prove

| Model | Example | Control flow source |
|-------|---------|-------------------|
| Finite automaton | #6 | C `if`/`else` |
| Minsky machine | #2 | C `for` loop |
| Turing machine | #11 | C `while` loop |
| Universal TM | #14 | C loop + switch |
| Lambda calculus | #12 | C recursion |
| Brainfuck | #13 | C `while` loop |
| CPU | #9 | C `switch` + loop |
| Self-interpreter | #16 | **`%n` hijacks return address** |

The first 15 examples prove that printf's memory primitives are sufficient for
TC *when combined with C's control flow*. Example #16 attempts to close the gap
by eliminating C control flow entirely, using `%n` to hijack the instruction
pointer directly.

## Security Implications

The `%n` write primitive is the root cause of **format string vulnerabilities**:

- `%n` can write to arbitrary memory addresses
- Attackers control the value written (character count, manipulated via width specifiers)
- This enables return-address overwrites, GOT hijacking, and arbitrary code execution

The Turing completeness angle is not just academic — it explains *why* format
string bugs are so dangerous. The same mechanism that could (in theory) make
printf a complete computer makes it an exploitation vector.

**Defense**: never pass user input as a printf format string.

## Historical Context

- **1967**: Minsky proved 2-counter machines are Turing complete
- **2000s**: Security researchers discovered `%n` enables arbitrary memory writes
- **2001**: Phrack article "Exploiting Format String Vulnerabilities"
- **2020s**: Academic papers formalized printf's computational power

## References

1. Minsky, M. (1967). *Computation: Finite and Infinite Machines*. Prentice-Hall.
2. Turing, A. M. (1936). "On Computable Numbers, with an Application to the Entscheidungsproblem". *Proceedings of the London Mathematical Society*.
3. Phrack Magazine. (2001). "Exploiting Format String Vulnerabilities".
4. Lattner, C. (2005). "Format string vulnerabilities". LLVM Blog.
