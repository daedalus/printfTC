# Turing Completeness of C printf

printf in C is **Turing complete**. This is not just a theoretical curiosity —
it has practical implications for security (format string vulnerabilities)
and demonstrates the surprising computational power hidden in standard library
functions.

This repository contains 15 C programs proving this through the `%n` format
specifier, which writes the number of characters printed so far to an arbitrary
memory location.

## The Core Mechanism

```c
int sum = 0;
printf("%*s%*s%n", a, "", b, "", &sum);  // sum = a + b
```

`%*s` prints exactly N spaces (when the string is `""`), and `%n` writes the
cumulative character count to `sum`. This creates a **read-modify-write cycle**
— the ALU of our printf computer.

## The Three Requirements for Turing Completeness

A system is Turing complete if it can simulate any Turing machine. This requires:

| Requirement | printf mechanism |
|------------|------------------|
| Conditional branching | C's `if`/`else`/`switch` |
| Arbitrary memory access | `%n` writes to any `int*` pointer |
| Unbounded iteration | C's `while`/`for` loops |

## Building and Running

```bash
make all          # compile all examples
make clean        # remove binaries

./01_counter      # run individual example
./09_memory_simulation
```

Requires `gcc` with C11 support.

## Examples

| # | File | What it demonstrates |
|---|------|----------------------|
| 1 | `src/01_counter.c` | Basic `%n` — writing character count to memory |
| 2 | `src/02_two_counter.c` | Minsky machine (2-counter machine, proven Turing complete) |
| 3 | `src/03_fibonacci.c` | Iterative Fibonacci via printf addition |
| 4 | `src/04_calculator.c` | Full ALU: add, subtract, multiply, divide, modulo, power |
| 5 | `src/05_conditional.c` | Conditional logic: min, max, abs, sign |
| 6 | `src/06_state_machine.c` | Finite automaton recognizing {a^n b^n | n >= 0} |
| 7 | `src/07_pointer_arithmetic.c` | Array/matrix operations via printf |
| 8 | `src/08_self_modifying.c` | Dynamic format strings and an interpreter |
| 9 | `src/09_memory_simulation.c` | CPU simulator: registers, RAM, ALU, instruction cycle |
| 10 | `src/10_ackermann.c` | Ackermann function (non-primitive-recursive) |
| 11 | `src/11_turing_machine.c` | Binary increment Turing machine |
| 12 | `src/12_lambda_calculus.c` | Church numerals, arithmetic, booleans, Y combinator |
| 13 | `src/13_formal_proof.c` | Brainfuck interpreter (minimal Turing-complete language) |
| 14 | `src/14_universal_machine.c` | Universal Turing machine (transition table as data) |
| 15 | `src/15_complex_example.c` | 4-element sorting network |

## How It Works

### Arithmetic via `%n`

```c
// Addition: a + b
int sum = 0;
printf("%*s%*s%n", a, "", b, "", &sum);

// Subtraction: a - b
int diff = 0;
printf("%*s%*s%n", a, "", -b, "", &diff);

// Multiplication: repeated addition
int product = 0;
for (int i = 0; i < b; i++)
    product = add(product, a);
```

### Memory Access via `%n`

```c
int ram[256] = {0};
int *cell = &ram[address];
printf("%*s%n", value, "", cell);  // ram[address] = value
```

### State Transitions

```c
int state = 0;
// Read symbol from tape
int symbol = tape[head];
// Transition: write new state via printf
printf("%*s%n", new_state, "", &state);
```

## Computational Hierarchy

```
printf + C
    |
    | simulates
    v
Minsky Machine (2-counter) --- proven Turing complete (Minsky, 1967)
    |
    | simulates
    v
Turing Machine
    |
    | equivalent to
    v
Lambda Calculus
```

## Historical Context

- **1967**: Minsky proved 2-counter machines are Turing complete
- **2000s**: Security researchers discovered `%n` enables arbitrary memory writes
- **2013**: Phrack article "Exploiting format strings" demonstrated practical attacks
- **2020s**: Academic papers formalized printf's computational power

## Security Implications

The Turing completeness of `%n` is the root cause of **format string vulnerabilities**:

- `%n` can write to arbitrary memory addresses
- Attackers control the value written (character count)
- This enables buffer overflows, return address overwrites, and arbitrary code execution

**Defense**: never pass user input as a printf format string.

## References

1. Minsky, M. (1967). *Computation: Finite and Infinite Machines*. Prentice-Hall.
2. Turing, A. M. (1936). "On Computable Numbers, with an Application to the Entscheidungsproblem". *Proceedings of the London Mathematical Society*.
3. Phrack Magazine. (2001). "Exploiting Format String Vulnerabilities".
4. Lattner, C. (2005). "Format string vulnerabilities". LLVM Blog.
