/*
 * Example 6: State Machine via printf
 *
 * Implements a finite state machine where:
 * - State is stored in a variable modified by %n
 * - Transitions are implemented via printf format strings
 * - Output depends on the current state
 *
 * This is a Moore machine that recognizes the language {a^n b^n | n >= 0}
 */
#include <stdio.h>
#include <string.h>

int main() {
    int state = 0;

    /* Input string: "aaabbb" - should be accepted (3 a's, 3 b's) */
    const char *input = "aaabbb";
    int a_count = 0, b_count = 0;

    printf("=== State Machine: Recognizing {a^n b^n | n >= 0} ===\n\n");
    printf("Input: \"%s\"\n\n", input);

    /* Initialize state = 0 (start) */
    printf("%*s%n", 0, "", &state);
    printf("Step 0: state = %d (start)\n", state);

    for (int i = 0; input[i] != '\0'; i++) {
        char c = input[i];

        if (state == 0 || state == 1) {
            /* In start or counting-a state */
            if (c == 'a') {
                /* Increment a_count: a_count = a_count + 1 */
                int old = a_count;
                a_count = 0;
                printf("%*s%*s%n", old, "", 1, "", &a_count);

                printf("Step %d: read '%c', a_count = %d\n", i + 1, c, a_count);

                /* Transition to state 1 (counting a's) */
                state = 0;
                printf("%*s%n", 1, "", &state);

            } else if (c == 'b' && a_count > 0) {
                /* First 'b' - switch to counting-b's state */
                b_count = 0;
                printf("%*s%*s%n", 0, "", 1, "", &b_count);

                state = 0;
                printf("%*s%n", 2, "", &state);
                printf("Step %d: read '%c', switch to state 2 (counting b's)\n", i + 1, c);

            } else {
                /* Invalid transition */
                state = 0;
                printf("%*s%n", 4, "", &state);  /* reject state */
                printf("Step %d: read '%c', REJECTED\n", i + 1, c);
                break;
            }

        } else if (state == 2) {
            /* Counting b's */
            if (c == 'b') {
                /* Increment b_count */
                int old = b_count;
                b_count = 0;
                printf("%*s%*s%n", old, "", 1, "", &b_count);
                printf("Step %d: read '%c', b_count = %d\n", i + 1, c, b_count);

            } else {
                state = 0;
                printf("%*s%n", 4, "", &state);
                printf("Step %d: read '%c', REJECTED (expected 'b')\n", i + 1, c);
                break;
            }
        }
    }

    /* Check if accepted */
    if (state != 4 && a_count == b_count) {
        state = 0;
        printf("%*s%n", 3, "", &state);
        printf("\nResult: ACCEPTED (a_count = b_count = %d)\n", a_count);
    } else {
        state = 0;
        printf("%*s%n", 4, "", &state);
        printf("\nResult: REJECTED (a_count = %d, b_count = %d)\n", a_count, b_count);
    }

    printf("\n=== State machines + counters = pushdown automata ===\n");
    printf("  With unbounded memory via printf, we exceed PDA power\n");

    return 0;
}
