# Turing Completeness of C printf

A collection of 15 C programs proving that `printf` is Turing complete through the `%n` format specifier, which writes the number of characters printed so far to an arbitrary memory location.

## The Core Mechanism

```c
int sum = 0;
printf("%*s%*s%n", a, "", b, "", &sum);  // sum = a + b
```

`%*s` prints exactly N spaces (when the string is `""`), and `%n` writes the cumulative character count to `sum`. This creates a **read-modify-write cycle** — the ALU of our printf computer.

## The Three Requirements for Turing Completeness

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
| 1 | `01_counter.c` | Basic `%n` — writing character count to memory |
| 2 | `02_two_counter.c` | Minsky machine (2-counter machine, proven Turing complete) |
| 3 | `03_fibonacci.c` | Iterative Fibonacci via printf addition |
| 4 | `04_calculator.c` | Full ALU: add, subtract, multiply, divide, modulo, power |
| 5 | `05_conditional.c` | Conditional logic: min, max, abs, sign |
| 6 | `06_state_machine.c` | Finite automaton recognizing {a^n b^n | n >= 0} |
| 7 | `07_pointer_arithmetic.c` | Array/matrix operations via printf |
| 8 | `08_self_modifying.c` | Dynamic format strings and an interpreter |
| 9 | `09_memory_simulation.c` | CPU simulator: registers, RAM, ALU, instruction cycle |
| 10 | `10_ackermann.c` | Ackermann function (non-primitive-recursive) |
| 11 | `11_turing_machine.c` | Binary increment Turing machine |
| 12 | `12_lambda_calculus.c` | Church numerals, arithmetic, booleans, Y combinator |
| 13 | `13_formal_proof.c` | Brainfuck interpreter (minimal Turing-complete language) |
| 14 | `14_universal_machine.c` | Universal Turing machine (transition table as data) |
| 15 | `15_complex_example.c` | 4-element sorting network |

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

## Security Implications

The Turing completeness of `%n` is the root cause of **format string vulnerabilities**:

- `%n` can write to arbitrary memory addresses
- Attackers control the value written (character count)
- This enables buffer overflows, return address overwrites, and arbitrary code execution

**Defense**: never pass user input as a printf format string.

## References

- Minsky, M. (1967). *Computation: Finite and Infinite Machines*. Prentice-Hall.
- Turing, A. M. (1936). "On Computable Numbers, with an Application to the Entscheidungsproblem". *Proceedings of the London Mathematical Society*.
- Phrack Magazine. (2001). "Exploiting Format String Vulnerabilities".
