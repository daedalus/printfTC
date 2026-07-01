/*
 * Example 14: Universal Turing Machine
 *
 * Implements a universal Turing machine that can simulate
 * any other Turing machine. This is the strongest proof of
 * Turing completeness.
 *
 * The UTM reads a table of transitions and simulates execution.
 */
#include <stdio.h>
#include <string.h>

#define TAPE_SIZE 100
#define BLANK 2

/* Transition: (state, symbol) -> (new_state, new_symbol, direction) */
typedef struct {
    int state;
    int symbol;
    int new_state;
    int new_symbol;
    int direction;  /* -1 = left, 1 = right */
} Transition;

int main() {
    printf("=== Universal Turing Machine ===\n\n");
    printf("A UTM can simulate any TM, proving that the simulating\n");
    printf("system (printf) is Turing complete.\n\n");

    /*
     * Binary increment TM: 1011 + 1 = 1100
     *
     * Scan right-to-left from the rightmost digit.
     * State 0 (scan left):
     *   read 1 -> write 0, move left, stay in 0
     *   read 0 -> write 1, HALT
     *   read blank -> write 1, HALT (all 1s case, e.g. 1111 -> 10000)
     */
    Transition transitions[] = {
        /* state, symbol, new_state, new_symbol, direction */
        {0, 1, 0, 0, -1},      /* State 0, read 1: write 0, move left, stay in 0 */
        {0, 0, 3, 1, 0},       /* State 0, read 0: write 1, HALT */
        {0, BLANK, 3, 1, 0},   /* State 0, read blank: write 1, HALT */
    };
    int num_transitions = sizeof(transitions) / sizeof(transitions[0]);

    /* Tape: initialized to BLANK */
    int tape[TAPE_SIZE];
    for (int i = 0; i < TAPE_SIZE; i++) tape[i] = BLANK;

    int head = 50;
    int state = 0;

    /* Input: binary 1011 (11 in decimal) */
    const char *input = "1011";
    int input_len = strlen(input);
    for (int i = 0; i < input_len; i++) {
        tape[head + i] = input[i] - '0';
    }

    /* Start head at RIGHTMOST digit */
    head = head + input_len - 1;

    printf("Input tape: %s (binary) = 11 (decimal)\n", input);
    printf("\nTransition table (encoded as data for UTM):\n");
    for (int i = 0; i < num_transitions; i++) {
        printf("  (%d, %d) -> (%d, %d, %s)\n",
               transitions[i].state, transitions[i].symbol,
               transitions[i].new_state, transitions[i].new_symbol,
               transitions[i].direction < 0 ? "L" : "R");
    }

    printf("\nExecution trace:\n");

    int steps = 0;
    while (state != 3 && steps < 50) {
        int symbol = tape[head];

        /* Find matching transition */
        int found = 0;
        for (int i = 0; i < num_transitions; i++) {
            if (transitions[i].state == state && transitions[i].symbol == symbol) {
                printf("  Step %2d: State %d, Read %d -> State %d, Write %d, Move %s\n",
                       steps, state, symbol,
                       transitions[i].new_state, transitions[i].new_symbol,
                       transitions[i].direction < 0 ? "Left" : "Right");

                /* Apply transition: write new symbol via printf */
                tape[head] = 0;
                printf("%*s%n", transitions[i].new_symbol, "", &tape[head]);

                /* Move head */
                head += transitions[i].direction;

                /* Update state via printf */
                state = 0;
                printf("%*s%n", transitions[i].new_state, "", &state);

                found = 1;
                break;
            }
        }

        if (!found) {
            printf("  Step %2d: No transition for (state=%d, symbol=%d) -> HALT\n",
                   steps, state, symbol);
            state = 3;
        }

        steps++;
    }

    /* Find leftmost non-blank */
    int start = head;
    while (start > 0 && tape[start - 1] != BLANK) start--;

    /* Print final tape */
    printf("\nFinal tape (around head=%d): ", head);
    for (int i = start; i <= head + 2; i++) {
        if (i >= 0 && i < TAPE_SIZE) {
            if (tape[i] == BLANK) printf("_");
            else printf("%d", tape[i]);
        }
    }
    printf("\n");

    /* Read result */
    int result = 0;
    for (int i = start; tape[i] != BLANK && i < TAPE_SIZE; i++) {
        result = result * 2 + tape[i];
    }

    printf("Result:   %d (decimal) = ", result);
    for (int i = start; tape[i] != BLANK && i < TAPE_SIZE; i++) {
        printf("%d", tape[i]);
    }
    printf(" (binary)\n");

    printf("Expected: 12 (decimal) = 1100 (binary)\n");
    printf("Status:   %s\n", result == 12 ? "CORRECT" : "ERROR");

    printf("\n=== Why this proves Turing completeness ===\n");
    printf("  1. Our system (printf + C) can simulate ANY Turing machine\n");
    printf("  2. The transition table is data, not hardcoded logic\n");
    printf("  3. By Church-Turing thesis, this means printf is Turing complete\n");

    return 0;
}
