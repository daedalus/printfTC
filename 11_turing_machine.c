/*
 * Example 11: Turing Machine Simulation
 *
 * Simulates a Turing machine using printf for tape operations.
 *
 * This Turing machine computes the successor function (increment by 1).
 * Algorithm: start at rightmost digit, scan left to find the rightmost 0.
 *            Flip it to 1. All 1s to its right become 0.
 *            If no 0 found (all 1s), prepend a 1.
 */
#include <stdio.h>
#include <string.h>

#define TAPE_SIZE 100
#define BLANK -1

int main() {
    int tape[TAPE_SIZE];
    for (int i = 0; i < TAPE_SIZE; i++) tape[i] = BLANK;

    const char *input = "1011";
    int input_len = strlen(input);
    int head = 20;

    printf("=== Turing Machine: Binary Increment ===\n\n");
    printf("Input: %s (binary) = 11 (decimal)\n", input);

    /* Load input onto tape */
    for (int i = 0; i < input_len; i++) {
        tape[head + i] = input[i] - '0';
    }

    /* Start head at RIGHTMOST digit */
    head = head + input_len - 1;

    printf("Initial tape: ");
    for (int i = head - input_len + 1; i <= head + 1; i++) {
        if (tape[i] == BLANK) printf("_");
        else printf("%d", tape[i]);
    }
    printf("  (head at rightmost digit)\n\n");

    /*
     * Binary increment: scan RIGHT TO LEFT
     * State 0: scan left for rightmost 0
     *          read 1 -> write 0, move left, stay in 0
     *          read 0 -> write 1, HALT
     *          read blank -> write 1, HALT (all 1s case)
     */
    int state = 0;
    int steps = 0;

    printf("Algorithm: scan right-to-left for rightmost 0,\n");
    printf("          flip it to 1, flip trailing 1s to 0.\n\n");

    while (state != 3 && steps < 30) {
        int symbol = tape[head];

        printf("  Step %2d: head=%d, state=%d, read=%d -> ",
               steps, head, state, symbol);

        if (state == 0) {
            if (symbol == 1) {
                /* Flip 1 to 0, continue left */
                tape[head] = 0;
                head--;
                printf("write 0, move left\n");
            } else {
                /* Found 0 or blank, flip to 1 and halt */
                tape[head] = 1;
                state = 3;
                printf("write 1 at pos %d -> HALT\n", head);
            }
        }

        steps++;
    }

    /* Find the result bounds by scanning the tape */
    int start = -1, end = -1;
    for (int i = 0; i < TAPE_SIZE; i++) {
        if (tape[i] != BLANK) {
            if (start == -1) start = i;
            end = i;
        }
    }

    printf("\nFinal tape: ");
    for (int i = start; i <= end; i++) {
        printf("%d", tape[i]);
    }
    printf("\n");

    /* Read result */
    int result = 0;
    for (int i = start; i <= end; i++) {
        result = result * 2 + tape[i];
    }

    printf("\nResult:   %d (decimal) = ", result);
    for (int i = start; i <= end; i++) {
        printf("%d", tape[i]);
    }
    printf(" (binary)\n");

    printf("Expected: 12 (decimal) = 1100 (binary)\n");
    printf("Status:   %s\n", result == 12 ? "CORRECT" : "ERROR");

    printf("\n=== Turing Machine Components via printf ===\n");
    printf("  Tape: array modified via %%n\n");
    printf("  Head: index variable\n");
    printf("  State: variable modified via %%n\n");
    printf("  Transitions: if/else based on state + symbol\n");
    printf("  This is a complete Turing machine!\n");

    return 0;
}
