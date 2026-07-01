/*
 * Example 3: Fibonacci Sequence Generator
 *
 * Demonstrates iterative computation using printf to:
 * 1. Store values in variables via %n
 * 2. Use stored values as arguments for subsequent operations
 * 3. Implement a loop-like pattern
 *
 * Key insight: %*s prints exactly N spaces (when string is ""),
 * while %*d prints at least 1 character (the digit itself).
 */
#include <stdio.h>

int main() {
    int a = 0, b = 0;
    int n = 10;

    printf("=== Fibonacci Sequence via printf ===\n\n");
    printf("F(1)  = 0\n");
    printf("F(2)  = 1\n");

    /* Set a = 0: print 0 spaces */
    printf("%*s%n", 0, "", &a);

    /* Set b = 1: print 1 space */
    printf("%*s%n", 1, "", &b);

    for (int i = 3; i <= n; i++) {
        int next = 0;

        /* Add a + b: print 'a' spaces then 'b' spaces */
        printf("%*s%*s%n", a, "", b, "", &next);

        printf("F(%d)  = %d\n", i, next);

        /* Shift: a = b, b = next */
        a = b;
        b = next;
    }

    printf("\n=== Computation achieved entirely through printf ===\n");
    printf("  Each iteration uses printf to:\n");
    printf("    1. Add two numbers (via %%*s width specifiers)\n");
    printf("    2. Store the result (via %%n)\n");
    printf("    3. Use stored values in the next iteration\n");

    return 0;
}
