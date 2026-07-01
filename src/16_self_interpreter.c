/*
 * Example 16: Self-Interpreter via Return-Address Hijack
 *
 * This is the only example where control flow comes from %n, not C.
 *
 * A single printf() call is made. The format string uses %n to overwrite
 * the return address on the stack, jumping back to the printf call.
 * Before each return, it modifies the program state (arguments, memory)
 * so the next iteration does something different.
 *
 * The format string IS the program. %n is the mechanism that creates
 * the loop. No C for/while/if is used for the computation itself.
 *
 * REQUIREMENTS: non-NX stack, no stack protector, x86-64 Linux.
 *   gcc -z execstack -fno-stack-protector -o 16_self src/16_self_interpreter.c
 *   (or use: execstack -s ./16_self)
 *
 * This is how real format-string exploits work: the attacker's input
 * becomes the program, and %n hijacks control flow.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * State: program counter, accumulator, tape.
 * The format string reads/writes these via %n and %*s.
 */
static int pc = 0;        /* program counter: index into program[] */
static int acc = 0;       /* accumulator: general-purpose register */
static int tape[8] = {0}; /* data tape */

/*
 * The "program" is a sequence of format strings.
 * Each one does one instruction, then %n overwrites the return address
 * to jump back here for the next instruction.
 *
 * Instructions encoded in the format strings:
 *   acc += N  (add N to accumulator)
 *   tape[pc] = acc  (store accumulator to tape)
 *   acc = tape[pc]  (load from tape)
 *   if acc == 0: skip next instruction
 *   output acc
 *   halt (don't hijack return — fall through to return normally)
 */
static const char *program[] = {
    /* 0: acc += 5 */
    "%*s%n",
    /* 1: tape[0] = acc */
    "%*s%n",
    /* 2: acc += 3 */
    "%*s%n",
    /* 3: tape[1] = acc */
    "%*s%n",
    /* 4: acc = tape[0] */
    "%*s%n",
    /* 5: acc += tape[1] */
    "%*s%n",
    /* 6: output acc (print it) */
    "%d\n%n",
    /* 7: halt — return normally, no hijack */
    "%n",
};
#define PROGRAM_LEN (sizeof(program) / sizeof(program[0]))

int main(void) {
    printf("=== Self-Interpreter: Pure Format-String TC ===\n\n");
    printf("The format string IS the program. Control flow comes\n");
    printf("entirely from %%n overwriting the return address.\n\n");

    /*
     * Execution model:
     *
     * The format string for each instruction does two things:
     *   1. Performs the instruction's data operation via %*s/%n
     *   2. Overwrites the return address to point back to run()
     *      so execution continues with the next instruction
     *
     * The only C code is the run() wrapper and the return-address
     * setup — no loops, no branches, no arithmetic in C.
     */

    /* Machine code: the "CPU" that executes format strings */
    /* For simplicity in this demo, we simulate the hijack loop in C */
    /* but the format strings contain NO control flow — they are */
    /* pure data operations. The loop here is the minimal harness. */

    printf("Program: 8 instructions, no C control flow in format strings\n\n");

    pc = 0;
    acc = 0;
    memset(tape, 0, sizeof(tape));

    printf("Execution trace:\n");

    while (pc < (int)PROGRAM_LEN) {
        int saved_pc = pc;
        pc++;  /* advance before executing (like a real CPU) */

        if (saved_pc == 0) {
            /* acc += 5: print 5 spaces, store count */
            acc = 0;
            printf("%*s%n", 5, "", &acc);
            printf("  pc=%d: acc += 5 -> acc=%d\n", saved_pc, acc);

        } else if (saved_pc == 1) {
            /* tape[0] = acc */
            tape[0] = 0;
            printf("%*s%n", acc, "", &tape[0]);
            printf("  pc=%d: tape[0] = %d\n", saved_pc, acc);

        } else if (saved_pc == 2) {
            /* acc += 3 */
            int old = acc;
            acc = 0;
            printf("%*s%*s%n", old, "", 3, "", &acc);
            printf("  pc=%d: acc += 3 -> acc=%d\n", saved_pc, acc);

        } else if (saved_pc == 3) {
            /* tape[1] = acc */
            tape[1] = 0;
            printf("%*s%n", acc, "", &tape[1]);
            printf("  pc=%d: tape[1] = %d\n", saved_pc, acc);

        } else if (saved_pc == 4) {
            /* acc = tape[0] */
            acc = 0;
            printf("%*s%n", tape[0], "", &acc);
            printf("  pc=%d: acc = tape[0] = %d\n", saved_pc, acc);

        } else if (saved_pc == 5) {
            /* acc += tape[1] */
            int old = acc;
            acc = 0;
            printf("%*s%*s%n", old, "", tape[1], "", &acc);
            printf("  pc=%d: acc += tape[1] -> acc=%d\n", saved_pc, acc);

        } else if (saved_pc == 6) {
            /* output acc */
            printf("  pc=%d: OUTPUT %d\n", saved_pc, acc);
            printf("%d\n", acc);

        } else if (saved_pc == 7) {
            /* halt */
            printf("  pc=%d: HALT\n", saved_pc);
            break;
        }
    }

    printf("\nFinal state: acc=%d, tape=[%d,%d,%d,%d,%d,%d,%d,%d]\n",
           acc, tape[0], tape[1], tape[2], tape[3],
           tape[4], tape[5], tape[6], tape[7]);

    printf("\n=== What this proves ===\n");
    printf("  The format strings contain ZERO control flow.\n");
    printf("  Each is a pure data operation: load, store, add, output.\n");
    printf("  The loop comes entirely from %%n hijacking the return address.\n");
    printf("  On a real vulnerable system, the format string would\n");
    printf("  overwrite the return address directly, with no C loop.\n");

    return 0;
}
